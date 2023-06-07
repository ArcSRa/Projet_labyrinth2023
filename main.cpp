#include "Lab_window.hpp"

int main(int argc, char* argv[]) {
    Gtk::Main app(argc, argv);

    LabWindow window(17, 17);

    Gtk::Main::run(window);

    return 0;
}
