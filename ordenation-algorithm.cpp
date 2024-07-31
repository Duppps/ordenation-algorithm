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
#include <Windows.h>
#include <codecvt>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::locale::global(std::locale("pt_BR.UTF-8"));
    return start_gtk_application(__argc, __argv);
}
