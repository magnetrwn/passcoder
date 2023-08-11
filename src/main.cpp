#include "window.hpp"
#include "memorable.hpp"
#include <iostream>

int
main(int argc, char* argv[]) {

    MemorableStringGen memorable("res/strings.json", "res/settings.json");

    Gtk::Main kit(argc, argv);
    WindowUI window("ui/classic.glade", "res/settings.json", memorable);
    window.run();

    return 0;
}
