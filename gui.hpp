#ifndef GUI_HPP
#define GUI_HPP

#include <gtk/gtk.h>

void activate_cb(GtkApplication* app, gpointer user_data);
int start_gtk_application(int argc, char** argv);
void button_clicked_cb(GtkWidget* widget, gpointer data);

#endif 
