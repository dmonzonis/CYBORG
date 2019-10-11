#include "MainWindow.h"

MainWindow::MainWindow()
{
}

lz::Window& MainWindow::get_window()
{
    static lz::Window window;
    return window;
}
