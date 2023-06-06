#include <gtkmm.h>
#include <iostream>
#include "Labyrinthe.hpp"

class MazeWindow : public Gtk::Window {
private:
  int width;
  int height;
  Labyrinthe labyrinthe;
  int playerX;
  int playerY;
  std::vector<std::vector<bool>> drawnLines;
protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
    
  /*    Gtk::Allocation allocation = get_allocation();
    const int width1 = allocation.get_width();
    const int height1 = allocation.get_height();*/
    const double cell_width = 600.0 / width;
    const double cell_height = 600.0 / height;
    //Aretes arretes=labyrinthe.aretes();
   //labyrinthe.reset();
    //labyrinthe.construire_aldous_broder();
  //labyrinthe.construire_fusion();
     //afficherCellMap(labyrinthe.getGraph(),labyrinthe, cell_width,cell_height);
      // const vector<vector<char>>& representation = labyrinthe.getRepr();
       labyrinthe.construire_repr();
 const vector<vector<char>>& repre = labyrinthe.getRepr();

    cr->set_source_rgb(1,1,1);
    cr -> move_to (0 , 0);
    cr->rectangle(0, 0, get_width(), get_height());
    cr->fill();

    cr->set_source_rgb(0.0, 0.0, 0.0); 
    cr->set_line_width(1.0); 
    cr->rectangle(0, 0, 600, 600);
    cr->stroke();
    cr->move_to(0,0);
    const cellMap& map=labyrinthe.getGraph();
    
    for (const auto& entry : map) {
  
    const cell& key = entry.first;
    const cellSet& values = entry.second;
    const cellSet voisins = labyrinthe.voisins_cellule(key);
     double y1 = key.first * cell_height;
     double x1 = key.second * cell_width;
     
    // Afficher la clé (cellule)
    cout << "Clé : (" << key.first << ", " << key.second << ")" << endl;
    
    // Afficher les valeurs (voisins de la cellule)
    cout << "Voisins :" << endl;
    for (const cell& neighbor : values) {
        cout << " (" << neighbor.first << ", " << neighbor.second << ")\n"; // voisin avec passage
        for (const auto& voisin : voisins) {
               double y2 = voisin.first * cell_height;
                double x2 = voisin.second * cell_width;
            if (values.find(voisin) == values.end()) {
   
                
                cout << "VRAI VOISIN : (" << voisin.first << ", " << voisin.second << ")" << endl; // voisin meme sans passage / cellule voisine avec mur entre
                cr->move_to(0,0);
                 if (y1 > y2) {
                    
                     cr->move_to(x1 , y1  );
                     cr->line_to(x1+ cell_width, y1 );
                     cr->stroke();
                     std::cout << "Mur vers le haut (rouge)" << std::endl;
                     // drawnLines[key.second][key.first] = true;
                 }

                if (x1 > x2) {
                  
                    cr->move_to(x1 , y1);
                    cr->line_to(x1 , y1 + cell_height);
                    cr->stroke();
                    std::cout << "Mur vers la gauche (bleu)" << std::endl;
                  //   drawnLines[key.second][key.first] = true;
                }

                if (y1 < y2) {
                  
                    cr->move_to(x1 , y1 + cell_height);
                    cr->line_to(x1 + cell_width, y1 + cell_height);
                    cr->stroke();
                    std::cout << "Mur vers le bas (vert)" << std::endl;
                    //  drawnLines[key.second][key.first] = true;
                }

                if (x1 < x2) {
                 
                    cr->move_to(x1 + cell_width, y1 );
                    cr->line_to(x1 + cell_width, y1 + cell_height);
                    cr->stroke();
                    std::cout << "Mur vers la droite (bleu cyan)" << std::endl;
                      //drawnLines[key.second][key.first] = true;
                }

             
            }
        
       
        }

    }
     
        cr->set_source_rgb(0.0, 1.0, 0.0);
        cr->rectangle(0, 0, cell_width, cell_height);
        cr->fill();
        cr->set_source_rgb(0.0, 0.0, 0.0);
         
          
        cr->set_source_rgb(1.0, 0.0, 0.0);
        cr->rectangle(cell_width*(width-1), cell_height*(height-1), cell_width, cell_height);
        cr->fill();
        cr->set_source_rgb(0.0, 0.0, 0.0);
         
}

cout << endl;
cout<<labyrinthe<<endl;
   

     
   // Dessiner le joueur
        cr->set_source_rgb(0.0, 0.0, 1.0); // Rouge
        const double playerX1 = playerX * cell_width;
        const double playerY1 = playerY * cell_height;
        cr->rectangle(playerX1, playerY1, cell_width, cell_height);
        cr->fill();

        return true;
    }

    bool on_key_press_event(GdkEventKey* event) override {
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
        }

        return true;
    }

    void movePlayer(int dx, int dy) {
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
                Gtk::MessageDialog dialog(*this, "Victoire !", false, Gtk::MESSAGE_INFO);
                dialog.set_secondary_text("Vous avez atteint la sortie du labyrinthe !");
                dialog.run();
            }
        }
    }
}


public:
  MazeWindow(int mazeWidth, int mazeHeight) : width(mazeWidth), height(mazeHeight), labyrinthe(mazeWidth, mazeHeight) {
    set_title("Labyrinthe");
    set_default_size(600, 600);
    set_position(Gtk::WIN_POS_CENTER);

   override_background_color(Gdk::RGBA("white"));

    
        playerX = 0;
        playerY = 0;

        add_events(Gdk::KEY_PRESS_MASK);
    //labyrinthe.reset();
   labyrinthe.construire_aldous_broder();

    //signal_draw().connect(sigc::mem_fun(*this, &MazeWindow::on_draw));
  

    show_all();
  }
  
};

int main(int argc, char* argv[]) {
  Gtk::Main app(argc, argv);

  MazeWindow window(10,11); 

  Gtk::Main::run(window);

  return 0;
}
