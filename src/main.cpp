#include "window.hpp"
#include "memorable.hpp"
#include <iostream>

int
main(int argc, char* argv[]) {

    MemorableStringGen memorable("res/adjectives.csv", "res/nouns.csv", "res/numbers.csv", "res/phonetic.csv");

    Gtk::Main kit(argc, argv);
    WindowUI window(memorable);
    window.run();

    return 0;
}
