#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <vector>
#include <gtkmm.h>

#include "memorable.hpp"

class WindowUI : public Gtk::Window {
private:
    MemorableStringGen memorable;

    // Glade UI builder
    Glib::RefPtr<Gtk::Builder> builder;

    // Main window
    Gtk::Window* main_window;

    Gtk::MenuItem* menu_file_quit;
    Gtk::MenuItem* menu_edit_settings;

    Gtk::Button* method_button;

    enum FieldRowIndex
    { INPUT1, INPUT2, INPUT3, INPUT4, OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4, fieldrows };
    enum FieldsIndex
    { LABEL, FIELD, BUTTON, fieldnum };
    std::vector<std::tuple<Gtk::Label*, Gtk::Entry*, Gtk::Button*>> fields;

    // Settings window
    Gtk::Window* settings_window;

    Gtk::ComboBoxText* settings_generator;

    Gtk::ToggleButton* settings_leetify;

    Gtk::Scale* scale_leet_rate;
    Gtk::Scale* scale_length;
    Gtk::Scale* scale_numbers;

    Gtk::Button* settings_apply_button;
    Gtk::Button* settings_defaults_button;

public:
    // Constructor
    WindowUI(MemorableStringGen memorable);
    void run();
    void quit();
};

#include "window.tpp"

#endif