#pragma once

#include <lazarus/Graphics.h>

/**
 * Singleton that stores and manages the main window of the game.
 */
class MainWindow
{
public:
    // Delete other constructors/copy operators
    MainWindow(const MainWindow&) = delete;
    MainWindow &operator=(const MainWindow&) = delete;
    MainWindow(MainWindow&&) = delete;
    MainWindow &operator=(MainWindow&&) = delete;

    /**
     * Get the instance to the main window.
     */
    static lz::Window& get_window();

private:
    MainWindow();  // Disable instantiation outside of this class
};
