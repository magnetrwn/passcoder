#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>

#include <gtkmm.h>

#include "memorable.hpp"
#include "actions.hpp"

class WindowUI {
public:
    WindowUI(const std::string &uiFile, const std::string &settingsFile, MemorableStringGen memorable);
    void run();
    void quit();

private:
    const std::string uiFile_, settingsFile_;

    MemorableStringGen memorable;

    // Glade UI builder

    Glib::RefPtr<Gtk::Builder> builder;

    // Main window

    Gtk::Window *main_window;

    Gtk::MenuItem *menu_file_quit;
    Gtk::MenuItem *menu_edit_settings;
    Gtk::MenuItem *menu_about;

    Gtk::Button *method_button;
    Gtk::ComboBoxText *method_select;

    enum FieldRowIndex
    { INPUT1, INPUT2, INPUT3, INPUT4, OUTPUT1, OUTPUT2, OUTPUT3, OUTPUT4, fieldrows };
    enum FieldsIndex
    { LABEL, FIELD, BUTTON, fieldnum };
    std::vector<std::tuple<Gtk::Label *, Gtk::Entry *, Gtk::Button *>> fields;

    Gtk::AboutDialog *about_window;

    // Settings window

    Gtk::Window *settings_window;

    Gtk::ComboBoxText *settings_generator;

    Gtk::ToggleButton *settings_leetify;

    Gtk::Scale *scale_leet_rate;
    Gtk::Scale *scale_length;
    Gtk::Scale *scale_numbers;

    Gtk::Label *label_leet_rate;
    Gtk::Label *label_length;
    Gtk::Label *label_numbers;

    Gtk::Button *settings_apply_button;
    Gtk::Button *settings_defaults_button;
};

#include "window.tpp"

#endif