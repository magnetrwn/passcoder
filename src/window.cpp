#include "window.hpp"
#include <iostream>
// TODO: fix mismatching use of pascalCase with snake_case namings!
WindowUI::WindowUI(MemorableStringGen memorable)
    : memorable(memorable) {

    // Setup GTKmm builder with Glade UI file
    builder = Gtk::Builder::create();
    try {
        builder->add_from_file(UI_FILENAME);
    } catch (const Glib::FileError& ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        throw 128;
    } catch (const Gtk::BuilderError& ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        throw 129;
    }

    // Assign nullptr to WindowUI widget pointers
    main_window = nullptr;
    method_button = nullptr;
    window_menu.resize(menuitems);
    for(auto& menu_item : window_menu)
        menu_item = nullptr;
    fields.resize(fieldrows);
    for(auto& field_row : fields) {
        std::get<LABEL>(field_row) = nullptr;
        std::get<FIELD>(field_row) = nullptr;
        std::get<BUTTON>(field_row) = nullptr;
    }

    // Initialize pointers for widgets
    builder->get_widget("main_window", main_window);
    if (!main_window) {
        std::cerr << "Unable to find Glade UI main_window in \"" << UI_FILENAME << "\"." << std::endl;
        throw 130;
    }
    builder->get_widget("method_button", method_button);

    builder->get_widget("menu_file_quit", window_menu[QUIT]);

    builder->get_widget("input1_label", std::get<LABEL>(fields[INPUT1]));
    builder->get_widget("input2_label", std::get<LABEL>(fields[INPUT2]));
    builder->get_widget("output1_label", std::get<LABEL>(fields[OUTPUT1]));
    builder->get_widget("output2_label", std::get<LABEL>(fields[OUTPUT2]));
    builder->get_widget("input1_field", std::get<FIELD>(fields[INPUT1]));
    builder->get_widget("input2_field", std::get<FIELD>(fields[INPUT2]));
    builder->get_widget("output1_field", std::get<FIELD>(fields[OUTPUT1]));
    builder->get_widget("output2_field", std::get<FIELD>(fields[OUTPUT2]));
    builder->get_widget("input1_button", std::get<BUTTON>(fields[INPUT1]));
    builder->get_widget("input2_button", std::get<BUTTON>(fields[INPUT2]));
    builder->get_widget("output1_button", std::get<BUTTON>(fields[OUTPUT1]));
    builder->get_widget("output2_button", std::get<BUTTON>(fields[OUTPUT2]));

    // Connect signals from widgets to functions using template
    safe_connect_signal(method_button, method_button->signal_clicked(), [](){});

    safe_connect_signal(window_menu[QUIT], window_menu[QUIT]->signal_activate(), [this](){
        this->quit();
    });

    safe_connect_signal(std::get<BUTTON>(fields[INPUT1]), std::get<BUTTON>(fields[INPUT1])->signal_clicked(), [this](){
        std::get<WindowUI::FieldsIndex::FIELD>(fields[WindowUI::FieldRowIndex::INPUT1])->set_text(this->memorable.getLeet());
    });
    safe_connect_signal(std::get<BUTTON>(fields[INPUT2]), std::get<BUTTON>(fields[INPUT2])->signal_clicked(), [this](){
        std::get<WindowUI::FieldsIndex::FIELD>(fields[WindowUI::FieldRowIndex::INPUT2])->set_text(this->memorable.getLeet());
    });
    safe_connect_signal(std::get<BUTTON>(fields[OUTPUT1]), std::get<BUTTON>(fields[OUTPUT1])->signal_clicked(), [this](){
        std::get<WindowUI::FieldsIndex::FIELD>(fields[WindowUI::FieldRowIndex::OUTPUT1])->set_text(this->memorable.getLeet());
    });
    safe_connect_signal(std::get<BUTTON>(fields[OUTPUT2]), std::get<BUTTON>(fields[OUTPUT2])->signal_clicked(), [this](){
        std::get<WindowUI::FieldsIndex::FIELD>(fields[WindowUI::FieldRowIndex::OUTPUT2])->set_text(this->memorable.getLeet());
    });
}

void WindowUI::run() {
    Gtk::Main::run(*main_window);
}

void WindowUI::quit() {
    Gtk::Main::quit();
}
