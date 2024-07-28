#include "gui.hpp"

void button_clicked_cb(GtkWidget* widget, gpointer data) {
    g_print("Button clicked!\n");
}

void activate_cb(GtkApplication* app, gpointer user_data) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hello GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    GtkStringList* string_list = gtk_string_list_new(NULL);
    gtk_string_list_append(string_list, "Bubble Sort");
    gtk_string_list_append(string_list, "Insertion Sort");
    gtk_string_list_append(string_list, "Selection Sort");
    gtk_string_list_append(string_list, "Quick Sort");
    gtk_string_list_append(string_list, "Shell Sort");

    GtkWidget* button = gtk_button_new_with_label("Click Me!");
    GtkWidget* drop_down = gtk_drop_down_new(G_LIST_MODEL(string_list), NULL);
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_cb), NULL);

    gtk_window_set_child(GTK_WINDOW(window), button);
    gtk_window_set_child(GTK_WINDOW(window), drop_down);

    gtk_widget_set_visible(window, true);
}

int start_gtk_application(int argc, char** argv) {
    GtkApplication* app = gtk_application_new("org.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
