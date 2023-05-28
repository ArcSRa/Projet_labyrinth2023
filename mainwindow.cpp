#include "mainwindow.h"

MainWindow::MainWindow()
{
    set_default_size(200, 200);

    Gtk::Box* main_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    add(*main_box);

    Gtk::Label* size_label = Gtk::manage(new Gtk::Label("Taille du labyrinthe (HxW) :"));
    main_box->pack_start(*size_label, Gtk::PACK_SHRINK);

    Gtk::Box* size_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    main_box->pack_start(*size_box, Gtk::PACK_SHRINK);

    height.set_placeholder_text("Hauteur");
    size_box->pack_start(height, Gtk::PACK_SHRINK);

    width.set_placeholder_text("Largeur");
    size_box->pack_start(width, Gtk::PACK_SHRINK);

    Gtk::Label* algo_label = Gtk::manage(new Gtk::Label("Algorithme :"));
    main_box->pack_start(*algo_label, Gtk::PACK_SHRINK);

    m_algo_combo.append("Fusion");
    m_algo_combo.append("Alduous-Broder");
    m_algo_combo.append("Autre");
    main_box->pack_start(m_algo_combo, Gtk::PACK_SHRINK);

    Gtk::Button* button = Gtk::manage(new Gtk::Button("Valider"));
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));
    main_box->pack_start(*button, Gtk::PACK_SHRINK);

    m_close_button.set_label("Close");
    m_close_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_close_button_clicked));
    main_box->pack_start(m_close_button, Gtk::PACK_SHRINK);

    show_all();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button_clicked()
{
    Glib::ustring height_str = height.get_text();
    Glib::ustring width_str = width.get_text();

    int height = 0, width = 0;

    try {
        height = std::stoi(height_str.raw());
        width = std::stoi(width_str.raw());
    }
    catch (const std::exception& e) {
        Gtk::MessageDialog dialog(*this, "Erreur", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
        dialog.set_secondary_text("Hauteur et largeur svp");
        dialog.run();
        return;
    }

   //hauteur et largeur à utiliser ici je pense

    Gtk::MessageDialog dialog("Paramètres sélectionnés !");
    dialog.run();
}

void MainWindow::on_close_button_clicked()
{
    close();
}
