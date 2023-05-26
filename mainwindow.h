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

    Gtk::SpinButton m_size_spin;
    Gtk::ComboBoxText m_algo_combo;
};

#endif // MAINWINDOW_H
