//pour compiler : g++ fenetre_graphique.cpp $(pkg-config gtkmm-3.0 --cflags --libs)


#include <gtkmm/application.h>
#include "vue.hpp"

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv);
    Vue vue;
    return app->run(vue);
}