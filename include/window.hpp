#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <vector>
#include <gtkmm.h>

class WindowUI : public Gtk::Window {
public:
    // Constructor
    WindowUI();
    void run();
    void quit();
private:
    // Glade UI builder
    Glib::RefPtr<Gtk::Builder> builder;

    // Pointers for widgets
    Gtk::Window* main_window;
    Gtk::Button* method_button;
    enum MenuItemIndex { QUIT, menuitems };
    std::vector<Gtk::MenuItem*> window_menu;
};

#include "window.tpp"

#endif