#include <iostream>
#include <vector>
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "quick_sort.hpp"
#include "shell_sort.hpp"
#include <gtk/gtk.h>
#include "gui.hpp"
#include <locale>
#include <codecvt>

int main(int argc, char **argv) {
    std::locale::global(std::locale("en_US.UTF-8"));
    return start_gtk_application(argc, argv);
}
