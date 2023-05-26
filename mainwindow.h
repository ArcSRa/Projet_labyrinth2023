#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

class MainWindow : public Gtk::Window
{
public:
    MainWindow();
    virtual ~MainWindow();

private:
    void on_button_clicked();
    void on_close_button_clicked();
    Gtk::Button m_close_button;
    Gtk::Entry height;
    Gtk::Entry width;
    Gtk::ComboBoxText m_algo_combo;
};

#endif // MAINWINDOW_H
