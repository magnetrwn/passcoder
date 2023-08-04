#include "window.hpp"
#include "memorable.hpp"
#include <iostream>

int main(int argc, char* argv[]) {

    MemorableStringGen wordgen("res/adjectives.csv", "res/nouns.csv");

    Gtk::Main kit(argc, argv);
    WindowUI window;
    window.run();

    return 0;
}
