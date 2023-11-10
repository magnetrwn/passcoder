#include "window.hpp"
#include "actions.hpp"

// TODO: naming consistency!

WindowUI::WindowUI(const std::string &uiFile, const std::string &settingsFile, MemorableStringGen memorable)
    : uiFile_(uiFile),
      settingsFile_(settingsFile),
      memorable(memorable) {

    // Setup GTKmm builder with Glade UI file
    builder = Gtk::Builder::create();
    try {
        builder->add_from_file(uiFile);
    } catch (const Glib::FileError &ex) {
        throw std::runtime_error("FileError: " + ex.what());
    } catch (const Gtk::BuilderError &ex) {
        throw std::runtime_error("BuilderError: " + ex.what());
    }

    // TODO: is this really necessary though...
    // Assign nullptr to WindowUI widget pointers
    main_window = nullptr;
    settings_window = nullptr;
    method_button = nullptr;

    menu_file_quit = nullptr;
    menu_edit_settings = nullptr;

    fields.resize(fieldrows);
    for (auto &field_row : fields) {
        std::get<LABEL>(field_row) = nullptr;
        std::get<FIELD>(field_row) = nullptr;
        std::get<BUTTON>(field_row) = nullptr;
    }

    // Initialize pointers and signals for main window widgets
    builder->get_widget("main_window", main_window);
    if (!main_window)
        throw std::runtime_error("Unable to find Glade UI main_window.");

    std::map<std::string, std::string> windowSettingsMap;
    windowSettingsMap = JSONUtil::getDictMap(JSONUtil::readJSON(settingsFile_), "window");
    int width, height;
    width = std::stoul(windowSettingsMap["width"]);
    height = std::stoul(windowSettingsMap["height"]);
    main_window->set_default_size(width, height);

    builder->get_widget("method_select", method_select);
    builder->get_widget("method_button", method_button);
    builder->get_widget("menu_file_quit", menu_file_quit);
    builder->get_widget("menu_edit_settings", menu_edit_settings);
    builder->get_widget("menu_about", menu_about);
    builder->get_widget("about_window", about_window);
    for (uint row = INPUT1; row < fieldrows; row++) {
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

        builder->get_widget(labelName, std::get<LABEL>(fields[static_cast<FieldRowIndex>(row)]));
        std::get<LABEL>(fields[static_cast<FieldRowIndex>(row)])->hide();
        builder->get_widget(fieldName, std::get<FIELD>(fields[static_cast<FieldRowIndex>(row)]));
        std::get<FIELD>(fields[static_cast<FieldRowIndex>(row)])->hide();
        builder->get_widget(buttonName, std::get<BUTTON>(fields[static_cast<FieldRowIndex>(row)]));
        std::get<BUTTON>(fields[static_cast<FieldRowIndex>(row)])->hide();
    }

    safe_connect_signal(menu_file_quit, menu_file_quit->signal_activate(), [this] {
        this->quit();
    });
    safe_connect_signal(main_window, main_window->signal_hide(), [this] {
        this->quit();
    });

    for (uint row = INPUT1; row < OUTPUT1; row++) {
        safe_connect_signal(std::get<BUTTON>(fields[row]),
        std::get<BUTTON>(fields[row])->signal_clicked(), [this, row] {
            std::get<WindowUI::FieldsIndex::FIELD>(fields[row])->set_text(this->memorable.get());
        });
    }
    safe_connect_signal(menu_about, menu_about->signal_activate(), [this] {
        this->about_window->show();
    });
    safe_connect_signal_rid(about_window, about_window->signal_response(),
    [this] (int response_id, Gtk::AboutDialog * dialog) {
        switch (response_id) {
        case Gtk::RESPONSE_CLOSE:
        case Gtk::RESPONSE_CANCEL:
        case Gtk::RESPONSE_DELETE_EVENT:
            dialog->hide();
            break;
        default:
            break;
        }
    });

    // Initialize pointers and signals for settings window widgets
    builder->get_widget("settings_window", settings_window);
    if (!main_window)
        throw std::runtime_error("Unable to find Glade UI settings_window.");

    builder->get_widget("settings_generator", settings_generator);
    builder->get_widget("settings_leetify", settings_leetify);
    builder->get_widget("scale_leet_rate", scale_leet_rate);
    builder->get_widget("scale_length", scale_length);
    builder->get_widget("scale_numbers", scale_numbers);
    builder->get_widget("label_leet_rate", label_leet_rate);
    builder->get_widget("label_length", label_length);
    builder->get_widget("label_numbers", label_numbers);
    builder->get_widget("settings_apply_button", settings_apply_button);
    builder->get_widget("settings_defaults_button", settings_defaults_button);

    // Displays widgets as default settings
    // TODO: default settings are not centralized, will need to refactor
    scale_leet_rate->show();
    label_leet_rate->show();
    scale_length->hide();
    label_length->hide();
    scale_numbers->hide();
    label_numbers->hide();

    // Always look at actually set settings
    safe_connect_signal(menu_edit_settings, menu_edit_settings->signal_activate(), [this] {
        this->settings_generator->set_active(this->memorable.getGenerator());
        this->settings_leetify->set_active(this->memorable.getLeet());
        this->scale_leet_rate->set_value(this->memorable.getLeetRandomness());
        this->scale_length->set_value(this->memorable.getTotalLength());
        this->scale_numbers->set_value(this->memorable.getWordCount());
        this->settings_window->show();
    });
    safe_connect_signal(settings_generator, settings_generator->signal_changed(), [this] {
        MemorableStringGen::GenSetting setting = MemorableStringGen::ustringToGenSetting(this->settings_generator->get_active_id());

        if (setting == MemorableStringGen::ADJ_AND_NOUN or setting == MemorableStringGen::PHONETIC_NOUN) {
            this->scale_length->hide();
            this->label_length->hide();
            this->scale_numbers->hide();
            this->label_numbers->hide();
        } else if (setting == MemorableStringGen::PHONETIC or setting == MemorableStringGen::NUMBERS) {
            this->scale_length->hide();
            this->label_length->hide();
            this->scale_numbers->show();
            this->label_numbers->show();
        } else if (setting == MemorableStringGen::HEXADECIMAL or setting == MemorableStringGen::ASCII) {
            this->scale_length->show();
            this->label_length->show();
            this->scale_numbers->hide();
            this->label_numbers->hide();
        }
    });
    safe_connect_signal(settings_leetify, settings_leetify->signal_toggled(), [this] {
        if (this->settings_leetify->get_active()) {
            scale_leet_rate->show();
            label_leet_rate->show();
        } else {
            scale_leet_rate->hide();
            label_leet_rate->hide();
        }
    });
    safe_connect_signal(settings_apply_button, settings_apply_button->signal_clicked(), [this] {
        this->memorable.setGenerator(MemorableStringGen::ustringToGenSetting(this->settings_generator->get_active_id()));
        this->memorable.setLeet(this->settings_leetify->get_active());
        this->memorable.setLeetRandomness(this->scale_leet_rate->get_value());
        this->memorable.setWordCount(this->scale_numbers->get_value());
        this->memorable.setTotalLength(this->scale_length->get_value());
        this->memorable.storeAsJSONDict();
        this->settings_window->hide();
    });
    safe_connect_signal(settings_defaults_button, settings_defaults_button->signal_clicked(), [this] {
        // TODO: default settings are not centralized, will need to refactor
        this->memorable.setToJSONDict("memorableDefaults");
        this->settings_window->hide();
    });

    safe_connect_signal(method_button, method_button->signal_clicked(), [this] {
        std::vector<std::string> inputs;
        for (uint row = INPUT1; row < OUTPUT1; row++)
            inputs.emplace_back(std::get<FIELD>(fields[row])->get_text().raw());

        std::vector<std::pair<std::string, std::string>> outputs = ActionTransform::transform(inputs, ActionTransform::ustringToAction(this->method_select->get_active_id()));

        uint row = OUTPUT1;
        for (std::pair<std::string, std::string> output : outputs) {
            std::get<LABEL>(fields[static_cast<WindowUI::FieldRowIndex>(row)])->set_text(output.first);
            std::get<FIELD>(fields[static_cast<WindowUI::FieldRowIndex>(row)])->set_text(output.second);
            row++;
        }
    });
}

void
WindowUI::run() {
    Gtk::Main::run(*main_window);
}

void
WindowUI::quit() {
    std::map<std::string, std::string> windowSettingsMap;

    int width, height;
    this->main_window->get_size(width, height);

    windowSettingsMap["width"] = std::to_string(width);
    windowSettingsMap["height"] = std::to_string(height);

    JSONUtil::storeMapAsDict(settingsFile_, "window", windowSettingsMap);
    Gtk::Main::quit();
}
