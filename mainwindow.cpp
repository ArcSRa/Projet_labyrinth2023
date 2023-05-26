#include "mainwindow.h"

MainWindow::MainWindow()
{
    set_default_size(200, 150);

    Gtk::Box* main_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    add(*main_box);

    Gtk::Label* size_label = Gtk::manage(new Gtk::Label("Taille du labyrinthe :"));
    main_box->pack_start(*size_label, Gtk::PACK_SHRINK);

    m_size_spin.set_range(5, 100);
    m_size_spin.set_increments(5, 5);
    m_size_spin.set_value(10);
    main_box->pack_start(m_size_spin, Gtk::PACK_SHRINK);

    Gtk::Label* algo_label = Gtk::manage(new Gtk::Label("Algorithme :"));
    main_box->pack_start(*algo_label, Gtk::PACK_SHRINK);

    m_algo_combo.append("Algorithme 1");
    m_algo_combo.append("Algorithme 2");
    m_algo_combo.append("Algorithme 3");
    main_box->pack_start(m_algo_combo, Gtk::PACK_SHRINK);

    Gtk::Button* button = Gtk::manage(new Gtk::Button("Valider"));
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));
    main_box->pack_start(*button, Gtk::PACK_SHRINK);

    show_all();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button_clicked()
{
    Gtk::MessageDialog dialog("Paramètres sélectionnés !");
    
    dialog.run();
}