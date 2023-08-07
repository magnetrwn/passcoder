#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <vector>
#include <gtkmm.h>

#include "memorable.hpp"

class WindowUI : public Gtk::Window {
private:
    // Glade UI builder
    Glib::RefPtr<Gtk::Builder> builder;

    // Widgets
    Gtk::Window* main_window;
    Gtk::Window* settings_window;

    Gtk::Button* method_button;

    enum MenuItemIndex { QUIT, menuitems };
    std::vector<Gtk::MenuItem*> window_menu;

    enum FieldRowIndex { INPUT1, INPUT2, INPUT3, INPUT4, OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4, fieldrows };
    enum FieldsIndex { LABEL, FIELD, BUTTON, fieldnum };
    std::vector<std::tuple<Gtk::Label*, Gtk::Entry*, Gtk::Button*>> fields;

    MemorableStringGen memorable;

public:
    // Constructor
    WindowUI(MemorableStringGen memorable);
    void run();
    void quit();
};

#include "window.tpp"

#endif