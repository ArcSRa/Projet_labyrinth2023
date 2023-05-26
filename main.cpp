#include "mainwindow.h"
#include <gtkmm.h>

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv);
    MainWindow main_window;
    return app->run(main_window);
}
