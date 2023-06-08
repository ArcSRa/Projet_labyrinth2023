#ifndef LABWINDOW_HPP
#define LABEWINDOW_HPP

#include <gtkmm.h>
#include <vector>
#include "Labyrinthe.hpp"

class LabWindow : public Gtk::Window {
private:
    int width;
    int height;
    Labyrinthe labyrinthe;
    int playerX;
    int playerY;
    std::vector<std::vector<bool>> drawnLines;
    int mazeWidth=3;
    int mazeHeight=3;
    std::string algorithm;
    bool showSolution=false;
    Gtk::ToggleButton toggleButton;
protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_key_press_event(GdkEventKey* event) override;
    void movePlayer(int dx, int dy);
    void showMenu();
    void on_toggle_button_clicked();
    void on_quit_clicked();
public:
    LabWindow(int mazeWidth, int mazeHeight);
};

#endif // LABWINDOW_HPP
