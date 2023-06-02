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
    const vector<vector<char>>& representation = labyrinthe.construire_aldous_broder();
    const double cell_width = 600.0 / width;
    const double cell_height = 600.0 / height;

    cr->set_source_rgb(1.0, 1.0, 1.0); 
    cr->paint(); 

    cr->set_source_rgb(0.0, 0.0, 0.0); 
    cr->set_line_width(1.0); 
    cr->rectangle(0, 0, 600, 600);
    

    for (int l = 0; l < height; l++) {
      for (int c = 0; c < width; c++) {
        double x = c * cell_width;
        double y = l * cell_height;
        cr->set_source_rgb(0.0, 0.0, 0.0); 
        if (representation[l][c] == '#') {//vertical droit
          cr->set_source_rgb(0.0, 1.0, 0.0); 
          cr->move_to(x+cell_width, y);
          
       
          cr->line_to(x+cell_width, y + cell_height);
         // cr->line_to(x, y); 
          cr->stroke(); 
        }
        else if (representation[l][c] == '&') {//vertical gauche
         cr->set_source_rgb(1.0, 0.0, 0.0); 
          cr->move_to(x- cell_width, y);
          
          cr->line_to(x - cell_width, y + cell_height);
        cr->stroke(); 
          //cr->line_to(x, y); 
        }
          else if (representation[l][c] == '_') {//horizontal bas
            cr->set_source_rgb(0.0, 0.0, 1.0); 
           cr->move_to(x, y- cell_height);
          
       
          cr->line_to(x+cell_width, y - cell_height);
           cr->stroke(); 
         //cr->line_to(x, y); 
         }
         else  if (representation[l][c] == '~') {//horizontal haut
                 cr->set_source_rgb(1.0, 0.0, 1.0); 
           cr->move_to(x, y+cell_height);
          
          cr->line_to(x +cell_width, y+cell_height);
           cr->stroke(); 
           //cr->line_to(x, y); 
         }
          else if (representation[l][c] == 'A') { //arrivé en rouge
           cr->move_to(x, y);
         
         
          cr->line_to(x + cell_width, y);
          cr->line_to(x + cell_width, y + cell_height);
          cr->line_to(x, y + cell_height);
          cr->line_to(x, y); // Ferme le chemin
        }
        else if (representation[l][c] == 'D') {//départ en bleu
         

          cr->move_to(x, y);
          cr->line_to(x + cell_width, y);
          cr->line_to(x + cell_width, y + cell_height);
          cr->line_to(x, y + cell_height);
          cr->line_to(x, y); // Ferme le chemin
        }
             
      
      }
    }

    cr->stroke(); 

    return true;
  }

public:
  MazeWindow(int mazeWidth, int mazeHeight) : width(mazeWidth), height(mazeHeight), labyrinthe(mazeWidth, mazeHeight) {
    set_title("Maze");
    set_default_size(600, 600);
    set_position(Gtk::WIN_POS_CENTER);

   override_background_color(Gdk::RGBA("white"));

    add_events(Gdk::BUTTON_PRESS_MASK);

    signal_draw().connect(sigc::mem_fun(*this, &MazeWindow::on_draw));
  labyrinthe.construire_aldous_broder();
  

    show_all();
  }
};

int main(int argc, char* argv[]) {
  Gtk::Main app(argc, argv);

  MazeWindow window(5, 5); 

  Gtk::Main::run(window);

  return 0;
}
