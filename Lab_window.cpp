#include "Lab_window.hpp"
#include <iostream>
#include <vector>
using namespace std;
LabWindow::LabWindow(int we, int he):bClose("Quitter") {
    set_title("Labyrinthe");
    set_default_size(1000, 600);
    set_position(Gtk::WIN_POS_CENTER);
    override_background_color(Gdk::RGBA("white"));

    playerX = 0;
    playerY = 0;
    showMenu();

    Gtk::Fixed* fixedContainer = Gtk::manage(new Gtk::Fixed());
   
    add(*fixedContainer);

  
 
    bClose.signal_clicked().connect(sigc::mem_fun(*this, &LabWindow::close));
 fixedContainer->set_size_request(15, 15);
    fixedContainer->put(bClose, 700, 350);
   const Cairo::RefPtr<Cairo::Context>& cr = get_window()->create_cairo_context();
   on_draw1(cr);
  afficher_j(cr);
    add_events(Gdk::KEY_PRESS_MASK);
    show_all();
}

void LabWindow::showMenu() {
    Gtk::Dialog dialog("Paramètres du labyrinthe", *this);
    dialog.add_button("_OK", Gtk::RESPONSE_OK);
    dialog.add_button("_Annuler", Gtk::RESPONSE_CANCEL);

    // Créer des widgets pour les options du menu
    Gtk::Label label_width("Largeur du labyrinthe :");
    Gtk::Entry entry_width;
    entry_width.set_text(to_string(mazeWidth));

    Gtk::Label label_height("Hauteur du labyrinthe :");
    Gtk::Entry entry_height;
    entry_height.set_text(to_string(mazeHeight));

    Gtk::Label label_algorithm("Algorithme de construction :");
    Gtk::ComboBoxText combo_algorithm;
    combo_algorithm.append("Aldous-Broder", "aldous-broder");
    combo_algorithm.append("Fusion", "fusion");
    combo_algorithm.set_active_id(" ");

    // Ajouter les widgets à la boîte de dialogue
    Gtk::Box* content_area = dialog.get_content_area();
    content_area->pack_start(label_width, Gtk::PACK_SHRINK);
    content_area->pack_start(entry_width, Gtk::PACK_SHRINK);
    content_area->pack_start(label_height, Gtk::PACK_SHRINK);
    content_area->pack_start(entry_height, Gtk::PACK_SHRINK);
    content_area->pack_start(label_algorithm, Gtk::PACK_SHRINK);
    content_area->pack_start(combo_algorithm, Gtk::PACK_SHRINK);

    dialog.show_all();

    int result = dialog.run();

    if (stoi(entry_width.get_text()) == 0 || stoi(entry_height.get_text()) == 0) {
        Gtk::MessageDialog dialog(*this, "Valeurs incorrectes", false, Gtk::MESSAGE_INFO);
        dialog.set_secondary_text("Si vous choisissez une taille nulle, le labyrinthe le sera aussi");
        dialog.run();
    }

    if (combo_algorithm.get_active_id() != "Fusion" && combo_algorithm.get_active_id() != "Aldous-Broder") {
        Gtk::MessageDialog dialog(*this, "Algorithme incorrect", false, Gtk::MESSAGE_INFO);
        dialog.run();
    }

    if (result == Gtk::RESPONSE_OK && stoi(entry_width.get_text()) != 0 && stoi(entry_height.get_text()) != 0) {
        // Récupérer les valeurs saisies
        mazeWidth = stoi(entry_width.get_text());
        mazeHeight = stoi(entry_height.get_text());
        algorithm = combo_algorithm.get_active_id();

        labyrinthe = Labyrinthe(mazeWidth, mazeHeight);

        if (algorithm == "Aldous-Broder") {
            labyrinthe.construire_aldous_broder();
        } else if (algorithm == "Fusion") {
            labyrinthe.construire_fusion();
        }
         
    }
}
void LabWindow::close () { Gtk :: Window :: close (); }
bool LabWindow::on_draw1(const Cairo::RefPtr<Cairo::Context>& cr) {
    width = mazeWidth;
    height = mazeHeight;

    const double cell_width = 600.0 / width;
    const double cell_height = 600.0 / height;

    labyrinthe.construire_repr();
    const vector<vector<char>>& repre = labyrinthe.getRepr();

    cr->set_source_rgb(1, 1, 1);
    cr->rectangle(0, 0, get_width(), get_height());
    cr->fill();

    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->set_line_width(1.0);
    cr->rectangle(0, 0, 600, 600);
    cr->stroke();
    cr->move_to(0, 0);

    const cellMap& map = labyrinthe.getGraph();

    for (const auto& entry : map) {
        const cell& key = entry.first;
        const cellSet& values = entry.second;
        const cellSet voisins = labyrinthe.voisins_cellule(key);
        double y1 = key.first * cell_height;
        double x1 = key.second * cell_width;

        //for (const cell& neighbor : values) {
            for (const auto& voisin : voisins) {
                double y2 = voisin.first * cell_height;
                double x2 = voisin.second * cell_width;
            //cout<<"voisin:"<<neighbor.first<<","<<neighbor.second<<endl;
                if (values.find(voisin) == values.end()) {
                    cr->move_to(0, 0);
                    if (y1 > y2) {
                        cr->move_to(x1, y1);
                        cr->line_to(x1 + cell_width, y1);
                        cr->stroke();
                    }

                    if (x1 > x2) {
                        cr->move_to(x1, y1);
                        cr->line_to(x1, y1 + cell_height);
                        cr->stroke();
                    }

                    if (y1 < y2) {
                        cr->move_to(x1, y1 + cell_height);
                        cr->line_to(x1 + cell_width, y1 + cell_height);
                        cr->stroke();
                    }

                    if (x1 < x2) {
                        cr->move_to(x1 + cell_width, y1);
                        cr->line_to(x1 + cell_width, y1 + cell_height);
                        cr->stroke();
                    }
                }
            }
        //}

        cr->set_source_rgb(0.0, 0.0, 0.0);
        cr->set_source_rgb(1.0, 0.0, 0.0);
        cr->rectangle(cell_width * (width - 1), cell_height * (height - 1), cell_width, cell_height);
        cr->fill();
        cr->set_source_rgb(0.0, 0.0, 0.0);
    }

 

   
        cr->set_font_size(14.0);
    cr->move_to(720, 370);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->show_text("Fermer");
    return true;
}
void LabWindow::afficher_j(const Cairo::RefPtr<Cairo::Context>& cr)
{ // Dessiner le joueur
    const double cell_width = 600.0 / width;
    const double cell_height = 600.0 / height;
    cr->set_source_rgb(0.0, 0.0, 1.0); // Rouge
    const double playerX1 = playerX * cell_width;
    const double playerY1 = playerY * cell_height;
    cr->rectangle(playerX1, playerY1, cell_width, cell_height);
    cr->fill();
    cr->set_font_size(14.0);
    cr->move_to(620, 250);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->show_text("Appuyer sur Espace pour voir la solution");
if (showSolution) {
        cr->move_to(0,0);
        cr->set_source_rgb(0.0, 1.0, 1.0);
        vector<cell> solution = labyrinthe.bfs(labyrinthe, make_pair(playerY, playerX), make_pair(height - 1, width - 1));
        for (const auto& cella : solution) {
            int y = cella.first * cell_height;
            int x = cella.second * cell_width;
            cr->rectangle(x+cell_width/4, y+cell_height/4, cell_width/2, cell_height/2);
            cr->fill();
        }
    }}
bool LabWindow::on_key_press_event(GdkEventKey* event)  {
    const Cairo::RefPtr<Cairo::Context>& cr = get_window()->create_cairo_context();
  afficher_j(cr);
  switch (event->keyval) {
    case GDK_KEY_Up:
      movePlayer(0, -1);
      break;
    case GDK_KEY_Down:
      movePlayer(0, 1);
      break;
    case GDK_KEY_Left:
      movePlayer(-1, 0);
      break;
    case GDK_KEY_Right:
      movePlayer(1, 0);
      break;
    case GDK_KEY_space:
      showSolution = !showSolution;
     
      queue_draw();
      break;
  }

  return true;
}


void LabWindow::movePlayer(int dx, int dy) {
   int newPlayerX = playerX + dx;
    int newPlayerY = playerY + dy;
    
    if (newPlayerX >= 0 && newPlayerX < width && newPlayerY >= 0 && newPlayerY < height) {
        // Vérifier si le mouvement est autorisé dans le labyrinthe
        cell currentCell(playerY, playerX);
        cell newCell(newPlayerY, newPlayerX);
        
        if (labyrinthe.arete(currentCell, newCell)) {
            // Mettre à jour la position du joueur
            playerX = newPlayerX;
            playerY = newPlayerY;
            
            // Redessiner la fenêtre
            queue_draw();
            
            // Vérifier si le joueur a atteint la sortie
            if (playerX == width - 1 && playerY == height - 1) {
                Gtk::MessageDialog dialog(*this, "Victoire ! Vous avez 20/20 !", false, Gtk::MESSAGE_INFO);
                dialog.set_secondary_text("Vous avez atteint la sortie du labyrinthe !");
                dialog.run();
            }
        }
    }
}

