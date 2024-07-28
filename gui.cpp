#include "gui.hpp"
#include <random>
#include <gtk/gtk.h>
#include <vector>
#include <string>
#include <iostream>
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "quick_sort.hpp"
#include "shell_sort.hpp"
#include "sort_order.hpp"
#include "file_handler.hpp"

std::string selected_algorithm_one;
std::string selected_algorithm_two;
int selected_nodes_quantity;
SortOrder sortOrder = SortOrder::Crescente;

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void sort_array_with_selected_algorithm(std::string algoritm) {
    std::vector<int> arr = FileHandler::genArray(sortOrder, selected_nodes_quantity);

    if (algoritm == "Bubble Sort") {
        BubbleSort bubbleSort;
        bubbleSort.sort(arr);
        std::cout << "Bubble Sorted array: ";
    }
    else if (algoritm == "Insertion Sort") {
        InsertionSort insertionSort;
        insertionSort.sort(arr);
        std::cout << "Insertion Sorted array: ";
    }
    else if (algoritm == "Selection Sort") {
        SelectionSort selectionSort;
        selectionSort.sort(arr);
        std::cout << "Selection Sorted array: ";
    }
    else if (algoritm == "Quick Sort") {
        QuickSort quickSort;
        quickSort.sort(arr);
        std::cout << "Quick Sorted array: ";
    }
    else if (algoritm == "Shell Sort") {
        ShellSort shellSort;
        shellSort.sort(arr);
        std::cout << "Shell Sorted array: ";
    }

    printArray(arr);
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
    sort_array_with_selected_algorithm(selected_algorithm_one);
    sort_array_with_selected_algorithm(selected_algorithm_two);
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
    gtk_window_set_title(GTK_WINDOW(window), "Comparar Algoritmos de Ordenação");
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

    GtkWidget* labelNodes = gtk_label_new("Escolha a quantidade de nós");
    GtkWidget* selectNodes = gtk_drop_down_new(G_LIST_MODEL(node_list), NULL);
    g_signal_connect(selectNodes, "notify::selected-item", G_CALLBACK(on_nodes_changed), NULL);
    on_nodes_changed(GTK_DROP_DOWN(selectNodes));

    gtk_box_append(GTK_BOX(vbox), labelNodes);
    gtk_box_append(GTK_BOX(vbox), selectNodes);

    GtkWidget* radioButtonOrderedAsc = gtk_check_button_new_with_label("Ordenados - ordem crescente");
    GtkWidget* radioButtonOrderedDesc = gtk_check_button_new_with_label("Ordenados - ordem decrescente");
    GtkWidget* radioButtonRandom = gtk_check_button_new_with_label("Ordem Aleatória");
    gtk_check_button_set_group(GTK_CHECK_BUTTON(radioButtonOrderedAsc), GTK_CHECK_BUTTON(radioButtonOrderedDesc));
    gtk_check_button_set_group(GTK_CHECK_BUTTON(radioButtonOrderedDesc), GTK_CHECK_BUTTON(radioButtonRandom));
    gtk_check_button_set_group(GTK_CHECK_BUTTON(radioButtonOrderedAsc), GTK_CHECK_BUTTON(radioButtonRandom));

    g_signal_connect(radioButtonOrderedAsc, "toggled", G_CALLBACK(on_order_changed), NULL);
    g_signal_connect(radioButtonOrderedDesc, "toggled", G_CALLBACK(on_order_changed), NULL);
    g_signal_connect(radioButtonRandom, "toggled", G_CALLBACK(on_order_changed), NULL);

    gtk_check_button_set_active(GTK_CHECK_BUTTON(radioButtonOrderedAsc), true);

    GtkWidget* labelOrder = gtk_label_new("Disposição dos dados");
    gtk_box_append(GTK_BOX(vbox), labelOrder);
    gtk_box_append(GTK_BOX(vbox), radioButtonOrderedAsc);
    gtk_box_append(GTK_BOX(vbox), radioButtonOrderedDesc);
    gtk_box_append(GTK_BOX(vbox), radioButtonRandom);

    GtkWidget* button = gtk_button_new_with_label("Executar");
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_cb), NULL);
    gtk_box_append(GTK_BOX(vbox), button);

    GtkWidget* textView = gtk_text_view_new();
    gtk_widget_set_size_request(textView, 400, 200);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textView), FALSE);
    gtk_box_append(GTK_BOX(vbox), textView);

    gtk_widget_set_visible(window, true);
}

int start_gtk_application(int argc, char** argv) {
    GtkApplication* app = gtk_application_new("org.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

