#include <gtkmm.h>
#include <iostream>
#include "Labyrinthe.hpp"

class MazeWindow : public Gtk::Window {
private:
  int width;
  int height;
  Labyrinthe labyrinthe;

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
  /*    Gtk::Allocation allocation = get_allocation();
    const int width1 = allocation.get_width();
    const int height1 = allocation.get_height();*/
    const double cell_width = 600.0 / width;
    const double cell_height = 600.0 / height;
    //Aretes arretes=labyrinthe.aretes();
   labyrinthe.reset();
    labyrinthe.construire_aldous_broder();
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
                 }

                if (x1 > x2) {
                  
                    cr->move_to(x1 , y1);
                    cr->line_to(x1 , y1 + cell_height);
                    cr->stroke();
                    std::cout << "Mur vers la gauche (bleu)" << std::endl;
                }

                if (y1 < y2) {
                  
                    cr->move_to(x1 , y1 + cell_height);
                    cr->line_to(x1 + cell_width, y1 + cell_height);
                    cr->stroke();
                    std::cout << "Mur vers le bas (vert)" << std::endl;
                }

                if (x1 < x2) {
                 
                    cr->move_to(x1 + cell_width, y1 );
                    cr->line_to(x1 + cell_width, y1 + cell_height);
                    cr->stroke();
                    std::cout << "Mur vers la droite (bleu cyan)" << std::endl;
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
   

     // cr->stroke(); 
  // int m_width=5;
  // int m_height=5;
  // cr->set_source_rgb(0.0, 0.0, 0.0);  // Couleur noire
  //       cr->set_line_width(1.0);
  //       for (int i = 0; i < width; ++i) {
  //           for (int j = 0; j < height; ++j) {
  //               double x = i * cell_width;
  //      double y = j * cell_height;
  //               cr->rectangle(x, y, width / m_width, height / m_height);
  //               cr->fill();
  //           }
  //       }

  //       // Dessiner les arêtes en blanc
  //       cr->set_source_rgb(1.0, 1.0, 1.0);  // Couleur blanche
  //       cr->set_line_width(2.0);
  //       for (const auto& arete : arretes) {
  //           const cell& cellule1 = arete.first;
  //           const cell& cellule2 = arete.second;
  //           const double x1 = cellule1.second * cell_width;
  //           const double y1 = cellule1.first * cell_height;
  //           const double x2 = cellule2.second *cell_width;
  //           const double y2 = cellule2.first * cell_height;
  //           cr->move_to(x1, y1);
  //           cr->line_to(x2, y2);
  //           cr->stroke();
  //       }

    return true;
  }

public:
  MazeWindow(int mazeWidth, int mazeHeight) : width(mazeWidth), height(mazeHeight), labyrinthe(mazeWidth, mazeHeight) {
    set_title("Labyrinthe");
    set_default_size(600, 600);
    set_position(Gtk::WIN_POS_CENTER);

   override_background_color(Gdk::RGBA("white"));

    add_events(Gdk::KEY_PRESS_MASK);
    //labyrinthe.reset();
   //labyrinthe.construire_aldous_broder();

    signal_draw().connect(sigc::mem_fun(*this, &MazeWindow::on_draw));
  

    show_all();
  }
  
};

int main(int argc, char* argv[]) {
  Gtk::Main app(argc, argv);

  MazeWindow window(10, 11); 

  Gtk::Main::run(window);

  return 0;
}
