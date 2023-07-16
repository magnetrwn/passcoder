#define DEBUG

#include "window.hpp"


int main(int argc, char* argv[]) {

    Gtk::Main kit(argc, argv);
    WindowUI window;
    window.run();

    return 0;
}
