#ifndef WINDOW_H_
#define WINDOW_H_

#include <vector>
#include <gtkmm.h>

class WindowUI : public Gtk::Window {
private:
    // Glade UI builder
    Glib::RefPtr<Gtk::Builder> builder;

    // Widgets
    Gtk::Window* main_window;
    Gtk::Button* method_button;
    enum MenuItemIndex { QUIT, menuitems };
    std::vector<Gtk::MenuItem*> window_menu;

public:
    // Constructor
    WindowUI();
    void run();
    void quit();
};

#include "window.tpp"

#endif