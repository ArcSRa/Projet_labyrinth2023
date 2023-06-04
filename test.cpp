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
    
    const double cell_width = 600.0 / width;
    const double cell_height = 600.0 / height;
    //Aretes arretes=labyrinthe.aretes();
   
    labyrinthe.construire_aldous_broder();
  
     //afficherCellMap(labyrinthe.getGraph(),labyrinthe, cell_width,cell_height);
      // const vector<vector<char>>& representation = labyrinthe.getRepr();
    
    cr->set_source_rgb(1.0, 1.0, 1.0); 
    cr->paint(); 

    cr->set_source_rgb(0.0, 0.0, 0.0); 
    cr->set_line_width(1.0); 
    cr->rectangle(0, 0, 600, 600);
    cr->stroke();
    const cellMap& map=labyrinthe.getGraph();
for (const auto& entry : map) {
  
    const cell& key = entry.first;
    const cellSet& values = entry.second;
    const cellSet voisins = labyrinthe.voisins_cellule(key);
     double y1 = key.first * cell_width;
     double x1 = key.second * cell_height;
    // Afficher la clé (cellule)
    cout << "Clé : (" << key.first << ", " << key.second << ")" << endl;
    
    // Afficher les valeurs (voisins de la cellule)
    cout << "Voisins :" << endl;
    for (const cell& neighbor : values) {
        cout << " (" << neighbor.first << ", " << neighbor.second << ")\n"; // voisin avec passage
        for (const auto& voisin : voisins) {
               double y2 = voisin.first * cell_width;
                double x2 = voisin.second * cell_height;
            if (values.find(voisin) == values.end()) {
              
                
                cout << "VRAI VOISIN : (" << voisin.first << ", " << voisin.second << ")" << endl; // voisin meme sans passage / cellule voisine avec mur entre
                
                if (y1>y2) {
                        cr->set_source_rgb(1.0, 0.0, 0.0); 
                        cr->move_to(y1-cell_width,x1+cell_height);
                        cr->line_to( y1+cell_width, x1+cell_height);
                        cr->stroke();
                        cout<<"haut(rouge)"<<endl;
                }
                  if(x1>x2){
                        cr->set_source_rgb(0.0, 0.0, 1.0); 
                      cr->move_to(   y1-cell_width   , x1-cell_width);
                        cr->line_to(  y1-cell_width  , x1+cell_width);
                        cr->stroke();
                        cout<<"gauche(bleu)"<<endl;
                }
                if (y1<y2) {
                        cr->set_source_rgb(0.0, 1.0, 0.0); 
                        cr->move_to(y1-cell_width,x1+cell_height);
                        cr->line_to( y1+cell_width, x1+cell_height);
                        cr->stroke();
                        cout<<"bas(vert)"<<endl;
                }
                  if(x1<x2){
                        cr->set_source_rgb(0.0, 1.0, 1.0); 
                      cr->move_to(  y1+cell_width , x1-cell_width);
                        cr->line_to(  y1+cell_width ,x1+cell_width);
                        cr->stroke();
                        cout<<"droite(bleu cyan)"<<endl;
                }
                
               /* if (key.first != voisin.first) {
                    if (voisin.first > key.first) {// Mur qui est horizontal bas entre les cellules
                        cr->set_source_rgb(0.0, 0.0, 1.0); 
                        cr->move_to(x, y );
                        cr->line_to(x + cell_width, y );
                        cr->stroke();
                    } 
                     if (voisin.first < key.first) {// Mur qui est horizontal haut entre les cellules
                        cr->set_source_rgb(1.0, 0.0, 1.0); 
                        cr->move_to(x, y + cell_height);
                        cr->line_to(x + cell_width, y + cell_height);
                        cr->stroke();
                    }
                } 
                if (key.first == voisin.first) {
                    if (voisin.second < key.second) {// Mur qui est vertical gauche entre les cellules
                        cr->set_source_rgb(1.0, 0.0, 0.0); 
                        cr->move_to(x - cell_width, y);
                        cr->line_to(x - cell_width, y + cell_height);
                        cr->stroke();
                    } 
                    if (voisin.second > key.second) {//mur qui est vertical droit entre les cellules
                        cr->set_source_rgb(0.0, 1.0, 0.0); 
                        cr->move_to(x + cell_width, y);
                        cr->line_to(x + cell_width, y + cell_height);
                        cr->stroke();
                    }
                }*/
            }
        }
    }
}

cout << endl;

   
     /*for (int l = 0; l < height; l++) {
     for (int c = 0; c < width; c++) {
       double x = c * cell_width;
        double y = l * cell_height;
          cr->set_source_rgb(0.0, 0.0, 0.0); 
           if (representation[l][c] != ' ') {
                     //  cr->set_source_rgb(0.0, 0.0, 0.0);
                       //cr->rectangle(x, y, cell_width, cell_height);
                       //cr->stroke(); cr->fill();
                  }
          if (representation[l][c] == '#') { //vertical droit
            cr->set_source_rgb(0.0, 1.0, 0.0); 
            cr->move_to(x+cell_width, y);
          
       
            cr->line_to(x+cell_width, y + cell_height);
            // cr->line_to(x, y); 
            cr->stroke(); 
          }
           if (representation[l][c] == '&') { //vertical gauche
           cr->set_source_rgb(1.0, 0.0, 0.0); 
            cr->move_to(x- cell_width, y);
          
            cr->line_to(x - cell_width, y + cell_height);
          cr->stroke(); 
             //cr->line_to(x, y); 
          }
             if (representation[l][c] == '_') { //horizontal bas
              cr->set_source_rgb(0.0, 0.0, 1.0); 
             cr->move_to(x, y- cell_height);
          
       
            cr->line_to(x+cell_width, y - cell_height);
             cr->stroke(); 
            //cr->line_to(x, y); 
           }
             if (representation[l][c] == '~') { //horizontal haut
                   cr->set_source_rgb(1.0, 0.0, 1.0); 
             cr->move_to(x, y+cell_height);
          
            cr->line_to(x +cell_width, y+cell_height);
             cr->stroke(); 
              //cr->line_to(x, y); 
           }
             if (representation[l][c] == 'A') {  //arrivé en rouge
             cr->move_to(x, y);
         
         
            cr->line_to(x + cell_width, y);
            cr->line_to(x + cell_width, y + cell_height);
            cr->line_to(x, y + cell_height);
            cr->line_to(x, y);   //Ferme le chemin
          }
           if (representation[l][c] == 'D') { //départ en bleu
         

            cr->move_to(x, y);
            cr->line_to(x + cell_width, y);
            cr->line_to(x + cell_width, y + cell_height);
            cr->line_to(x, y + cell_height);
            cr->line_to(x, y);   //Ferme le chemin
          }
             
      
        }
      }

      cr->stroke(); */
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
    set_title("Maze");
    set_default_size(600, 600);
    set_position(Gtk::WIN_POS_CENTER);

   override_background_color(Gdk::RGBA("white"));

    add_events(Gdk::KEY_PRESS_MASK);
   // labyrinthe.construire_aldous_broder();

    signal_draw().connect(sigc::mem_fun(*this, &MazeWindow::on_draw));
  

    show_all();
  }
};

int main(int argc, char* argv[]) {
  Gtk::Main app(argc, argv);

  MazeWindow window(5, 5); 

  Gtk::Main::run(window);

  return 0;
}
