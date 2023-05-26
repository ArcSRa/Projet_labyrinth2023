#include "mainwindow.h"
#include <gtkmm.h>
//g++ main.cpp mainwindow.cpp -o labyrinth_app `pkg-config gtkmm-3.0 --cflags --libs`
int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv);
    MainWindow main_window;
    return app->run(main_window);
}
