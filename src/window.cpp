#include "window.hpp"


WindowUI::WindowUI() {
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
    for(auto menu_item : window_menu)
        menu_item = nullptr;

    // Initialize pointers for widgets
    builder->get_widget("main_window", main_window);
    if (!main_window) {
        std::cerr << "UI: Unable to find main_window in \"" << UI_FILENAME << "\"." << std::endl;
        throw 130;
    }
    builder->get_widget("method_button", method_button);
    builder->get_widget("menu_file_quit", window_menu[QUIT]);

    // Connect signals from widgets to functions using template
    safe_connect_signal(method_button, method_button->signal_clicked(), [](){});
    safe_connect_signal(window_menu[QUIT], window_menu[QUIT]->signal_activate(), [this](){
        this->quit();
    });
}

void WindowUI::run() {
    Gtk::Main::run(*main_window);
}

void WindowUI::quit() {
    Gtk::Main::quit();
}
