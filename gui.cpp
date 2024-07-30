#include "gui.hpp"
#include <random>
#include <gtk/gtk.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "quick_sort.hpp"
#include "shell_sort.hpp"
#include "sort_order.hpp"
#include "file_handler.hpp"
#include <map>

std::string selected_algorithm_one;
std::string selected_algorithm_two;
int selected_nodes_quantity;
SortOrder sortOrder = SortOrder::Crescente;

void printStats(GtkTextBuffer* buffer, const std::string& algoName, double comparisons, double movements, double duration) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring algoNameW = converter.from_bytes(algoName);
    std::wostringstream statsStream;
    statsStream << algoNameW << L":\n"
        << L"Tempo de execução: " << std::fixed << std::setprecision(0) << duration << L" segundos\n"
        << L"Número de comparações: " << std::fixed << std::setprecision(0) << comparisons << L"\n"
        << L"Número de movimentações: " << std::fixed << std::setprecision(0) << movements << L"\n"
        << L"--------------------------------------\n";
    std::wstring stats = statsStream.str();
    std::string statsStr = converter.to_bytes(stats);

    if (GTK_IS_TEXT_BUFFER(buffer)) {
        GtkTextIter endIter;
        gtk_text_buffer_get_end_iter(buffer, &endIter);
        gtk_text_buffer_insert(buffer, &endIter, statsStr.c_str(), -1);
    }
}

void printAlgorithmComparisonStats(const std::map<std::string, int>& algorithmOne, const std::map<std::string, int>& algorithmTwo, GtkTextBuffer* buffer) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wostringstream comparisonStream;

    comparisonStream << L"Diferenças entre algoritmos:\n";    
        
        double durationDifference = algorithmOne.at("Duration") - algorithmTwo.at("Duration");
        double comparisonsDifference = algorithmOne.at("Comparisons") - algorithmTwo.at("Comparisons");
        double movementsDifference = algorithmOne.at("Movements") - algorithmTwo.at("Movements");

        comparisonStream << L"\nDiferença no Tempo de execução: " << std::fixed << std::setprecision(6) << durationDifference << L" segundos\n"
            << L"Diferença no Número de comparações: " << std::fixed << std::setprecision(0) << comparisonsDifference << L"\n"
            << L"Diferença no Número de movimentações: " << std::fixed << std::setprecision(0) << movementsDifference << L"\n";

        comparisonStream << L"\nResultado:\n";

        if (durationDifference < 0 && comparisonsDifference < 0 && movementsDifference < 0) {
            comparisonStream << L"O algoritmo um foi melhor em todos os critérios.\n";
        }
        else if (durationDifference > 0 && comparisonsDifference > 0 && movementsDifference > 0) {
            comparisonStream << L"O algoritmo dois foi melhor em todos os critérios.\n";
        }
        else {
            comparisonStream << L"Mesma coisa.\n";
        }

        std::wstring comparisonStats = comparisonStream.str();
        std::string comparisonStatsStr = converter.to_bytes(comparisonStats);

        if (g_utf8_validate(comparisonStatsStr.c_str(), -1, NULL)) {
            if (GTK_IS_TEXT_BUFFER(buffer)) {
                GtkTextIter endIter;
                gtk_text_buffer_get_end_iter(buffer, &endIter);
                gtk_text_buffer_insert(buffer, &endIter, comparisonStatsStr.c_str(), -1);
            }
        }
        else {
            std::cerr << "Erro: Texto não é UTF-8 válido.\n";
        }
       
}


std::map<std::string, int> sort_array_with_selected_algorithm(GtkTextBuffer* buffer, const std::string& algorithm) {
    std::vector<int> arr = FileHandler::genArray(sortOrder, selected_nodes_quantity);

    SortAlgorithm* currentAlgo = nullptr;
    std::map<std::string, int> statsMap;

    if (algorithm == "Bubble Sort") {
        currentAlgo = new BubbleSort();
    }
    else if (algorithm == "Insertion Sort") {
        currentAlgo = new InsertionSort();
    }
    else if (algorithm == "Selection Sort") {
        currentAlgo = new SelectionSort();
    }
    else if (algorithm == "Quick Sort") {
        currentAlgo = new QuickSort();
    }
    else if (algorithm == "Shell Sort") {
        currentAlgo = new ShellSort();
    }

    if (currentAlgo) {
        auto start = std::chrono::high_resolution_clock::now();
        currentAlgo->sort(arr);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        statsMap["Duration"] = duration.count();
        statsMap["Comparisons"] = currentAlgo->getComparisons();
        statsMap["Movements"] = currentAlgo->getMovements();

        delete currentAlgo;
    }

    return statsMap;
}

std::string removeDots(const std::string& input) {
    std::string output = input;
    output.erase(std::remove(output.begin(), output.end(), '.'), output.end());
    return output;
}

void on_algorithm_one_changed(GtkDropDown* dropdown) {
    GtkStringObject* string_obj = GTK_STRING_OBJECT(gtk_drop_down_get_selected_item(dropdown));
    selected_algorithm_one = gtk_string_object_get_string(string_obj);
}

void on_algorithm_two_changed(GtkDropDown* dropdown) {
    GtkStringObject* string_obj = GTK_STRING_OBJECT(gtk_drop_down_get_selected_item(dropdown));
    selected_algorithm_two = gtk_string_object_get_string(string_obj);
}

void on_nodes_changed(GtkDropDown* dropdown) {
    GtkStringObject* string_obj = GTK_STRING_OBJECT(gtk_drop_down_get_selected_item(dropdown));
    selected_nodes_quantity = std::stoi(removeDots(gtk_string_object_get_string(string_obj)));
}

void button_clicked_cb(GtkWidget* widget, gpointer data) {
    GtkTextBuffer* buffer = GTK_TEXT_BUFFER(data);
    gtk_text_buffer_set_text(buffer, "", -1);

    std::map<std::string, int> statsAlgorithmOne = sort_array_with_selected_algorithm(buffer, selected_algorithm_one);
    std::map<std::string, int> statsAlgorithmTwo = sort_array_with_selected_algorithm(buffer, selected_algorithm_two);

    printStats(buffer, selected_algorithm_one, statsAlgorithmOne["Comparisons"], statsAlgorithmOne["Movements"], statsAlgorithmOne["Duration"]);
    printStats(buffer, selected_algorithm_two, statsAlgorithmTwo["Comparisons"], statsAlgorithmTwo["Movements"], statsAlgorithmTwo["Duration"]);
    printAlgorithmComparisonStats(statsAlgorithmOne, statsAlgorithmTwo, buffer);
}

void on_order_changed(GtkCheckButton* toggle_button, gpointer user_data) {
    if (gtk_check_button_get_active(toggle_button)) {
        const gchar* label = gtk_check_button_get_label(toggle_button);

        if (g_strcmp0(label, "Ordenados - ordem crescente") == 0) {
            sortOrder = SortOrder::Crescente;
        }
        else if (g_strcmp0(label, "Ordenados - ordem decrescente") == 0) {
            sortOrder = SortOrder::Decrescente;
        }
        else if (g_strcmp0(label, "Ordem Aleatória") == 0) {
            sortOrder = SortOrder::Random;
        }
    }
}

void activate_cb(GtkApplication* app, gpointer user_data) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), u8"Comparar Algoritmos de Ordenação");
    gtk_window_set_default_size(GTK_WINDOW(window), 480, 640);

    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_margin_start(vbox, 20);
    gtk_widget_set_margin_end(vbox, 20);
    gtk_widget_set_margin_top(vbox, 20);
    gtk_widget_set_margin_bottom(vbox, 20);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    GtkWidget* hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget* vboxAlgorithmOne = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget* vboxAlgorithmTwo = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(hbox), vboxAlgorithmOne);
    gtk_box_append(GTK_BOX(hbox), vboxAlgorithmTwo);
    gtk_box_append(GTK_BOX(vbox), hbox);

    GtkStringList* string_list = gtk_string_list_new(NULL);
    gtk_string_list_append(string_list, "Bubble Sort");
    gtk_string_list_append(string_list, "Insertion Sort");
    gtk_string_list_append(string_list, "Selection Sort");
    gtk_string_list_append(string_list, "Quick Sort");
    gtk_string_list_append(string_list, "Shell Sort");

    GtkWidget* labelAlgorithmOne = gtk_label_new("Algoritmo 1: ");
    GtkWidget* selectAlgorithmOne = gtk_drop_down_new(G_LIST_MODEL(string_list), NULL);
    g_signal_connect(selectAlgorithmOne, "notify::selected-item", G_CALLBACK(on_algorithm_one_changed), NULL);
    on_algorithm_one_changed(GTK_DROP_DOWN(selectAlgorithmOne));

    GtkWidget* labelAlgorithmTwo = gtk_label_new("Algoritmo 2: ");
    GtkWidget* selectAlgorithmTwo = gtk_drop_down_new(G_LIST_MODEL(string_list), NULL);
    g_signal_connect(selectAlgorithmTwo, "notify::selected-item", G_CALLBACK(on_algorithm_two_changed), NULL);
    on_algorithm_two_changed(GTK_DROP_DOWN(selectAlgorithmTwo));

    gtk_box_append(GTK_BOX(vboxAlgorithmOne), labelAlgorithmOne);
    gtk_box_append(GTK_BOX(vboxAlgorithmOne), selectAlgorithmOne);

    gtk_box_append(GTK_BOX(vboxAlgorithmTwo), labelAlgorithmTwo);
    gtk_box_append(GTK_BOX(vboxAlgorithmTwo), selectAlgorithmTwo);

    GtkStringList* node_list = gtk_string_list_new(NULL);
    gtk_string_list_append(node_list, "1.000");
    gtk_string_list_append(node_list, "10.000");
    gtk_string_list_append(node_list, "100.000");
    gtk_string_list_append(node_list, "1.000.000");

    GtkWidget* labelNodes = gtk_label_new(u8"Escolha a quantidade de nós");
    GtkWidget* selectNodes = gtk_drop_down_new(G_LIST_MODEL(node_list), NULL);
    g_signal_connect(selectNodes, "notify::selected-item", G_CALLBACK(on_nodes_changed), NULL);
    on_nodes_changed(GTK_DROP_DOWN(selectNodes));

    gtk_box_append(GTK_BOX(vbox), labelNodes);
    gtk_box_append(GTK_BOX(vbox), selectNodes);

    GtkWidget* radioButtonOrderedAsc = gtk_check_button_new_with_label("Ordenados - ordem crescente");
    GtkWidget* radioButtonOrderedDesc = gtk_check_button_new_with_label("Ordenados - ordem decrescente");
    GtkWidget* radioButtonRandom = gtk_check_button_new_with_label(u8"Ordem Aleatória");
    gtk_check_button_set_group(GTK_CHECK_BUTTON(radioButtonOrderedAsc), GTK_CHECK_BUTTON(radioButtonOrderedDesc));
    gtk_check_button_set_group(GTK_CHECK_BUTTON(radioButtonOrderedDesc), GTK_CHECK_BUTTON(radioButtonRandom));
    gtk_check_button_set_group(GTK_CHECK_BUTTON(radioButtonOrderedAsc), GTK_CHECK_BUTTON(radioButtonRandom));

    g_signal_connect(radioButtonOrderedAsc, "toggled", G_CALLBACK(on_order_changed), NULL);
    g_signal_connect(radioButtonOrderedDesc, "toggled", G_CALLBACK(on_order_changed), NULL);
    g_signal_connect(radioButtonRandom, "toggled", G_CALLBACK(on_order_changed), NULL);

    gtk_check_button_set_active(GTK_CHECK_BUTTON(radioButtonOrderedAsc), true);

    GtkWidget* labelOrder = gtk_label_new(u8"Disposição dos dados");
    gtk_box_append(GTK_BOX(vbox), labelOrder);
    gtk_box_append(GTK_BOX(vbox), radioButtonOrderedAsc);
    gtk_box_append(GTK_BOX(vbox), radioButtonOrderedDesc);
    gtk_box_append(GTK_BOX(vbox), radioButtonRandom);

    GtkWidget* button = gtk_button_new_with_label("Executar");
    gtk_box_append(GTK_BOX(vbox), button);

    GtkWidget* textView = gtk_text_view_new();
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    gtk_widget_set_size_request(textView, 400, 200);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), FALSE);
    gtk_box_append(GTK_BOX(vbox), textView);

    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_cb), buffer);

    gtk_widget_set_visible(window, true);
}

int start_gtk_application(int argc, char** argv) {
    GtkApplication* app = gtk_application_new("org.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
