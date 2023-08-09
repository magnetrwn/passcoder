#include "window.hpp"

// TODO: naming consistency!

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

    // TODO: is this really necessary though...
    // Assign nullptr to WindowUI widget pointers
    main_window = nullptr;
    settings_window = nullptr;
    method_button = nullptr;

    menu_file_quit = nullptr;
    menu_edit_settings = nullptr;

    fields.resize(fieldrows);
    for (auto& field_row : fields) {
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
    builder->get_widget("settings_window", settings_window);
    if (!main_window) {
        std::cerr << "Unable to find Glade UI settings_window in \"" << UI_FILENAME << "\"." << std::endl;
        throw 130;
    }

    builder->get_widget("method_button", method_button);

    builder->get_widget("menu_file_quit", menu_file_quit);
    builder->get_widget("menu_edit_settings", menu_edit_settings);

    for (int row = INPUT1; row < fieldrows; row++) {
        std::string nameBeginning, nameNumber;
        if (row < OUTPUT1) {
            nameBeginning = "input";
            nameNumber = std::to_string(row + 1);
        } else {
            nameBeginning = "output";
            nameNumber = std::to_string(row - 3);
        }
        std::string labelName = nameBeginning + nameNumber + "_label";
        std::string fieldName = nameBeginning + nameNumber + "_field";
        std::string buttonName = nameBeginning + nameNumber + "_button";

        builder->get_widget(labelName, std::get<LABEL>(fields[row]));
        builder->get_widget(fieldName, std::get<FIELD>(fields[row]));
        builder->get_widget(buttonName, std::get<BUTTON>(fields[row]));
    }

    // Connect signals from widgets to functions using template
    safe_connect_signal(method_button, method_button->signal_clicked(), [this] {
        this->settings_window->show();
    });
    safe_connect_signal(menu_edit_settings, menu_edit_settings->signal_activate(), [this] {
        this->settings_window->show();
    });
    safe_connect_signal(menu_file_quit, menu_file_quit->signal_activate(), [this] {
        this->quit();
    });
    for (int row = INPUT1; row < fieldrows; row++) {
        safe_connect_signal(std::get<BUTTON>(fields[row]),
        std::get<BUTTON>(fields[row])->signal_clicked(), [this, row] {
            std::get<WindowUI::FieldsIndex::FIELD>(fields[row])->set_text(this->memorable.get());
        });
    }
}

void
WindowUI::run() {
    Gtk::Main::run(*main_window);
}

void
WindowUI::quit() {
    Gtk::Main::quit();
}
