#pragma once
#include <gtkmm.h>
class Grille : public Gtk :: DrawingArea {
private :
const int largeur = 400;
const int hauteur = 300;
const int CoteCase=80;
public :
Grille () {
this -> signal_draw (). connect ( sigc :: mem_fun (* this , & Grille :: on_draw ));

this -> set_size_request ( this -> largeur , this -> hauteur );

}
virtual ~ Grille () {}
protected :
bool on_draw (  const Cairo :: RefPtr < Cairo :: Context >& cr ) override {
 cr->set_source_rgb(0,0,0);
 cr -> move_to (0 , 0);
cr->rectangle(0, 0, get_width(), get_height());
cr->fill();
// tracer une ligne verte entre les points (10,10) et (200, 240)
cr -> set_source_rgb (255 , 255, 255);

for(int i=0;i<6;i++){//i:hauteur
    for(int j=0;j<4;j++) //j:longeur
    {
        cr -> move_to (0,0);
       cr->rectangle(i*CoteCase,j*CoteCase,80,80);
        cr -> stroke ();

     
    }
}


// // tracer un cercle bleu en (200, 55) de rayon 30 pixlels
// cr -> set_source_rgb (0 , 0 , 1);
// cr -> arc (200 , 55 , 30 , 0.0 , 2 * M_PI );
// cr -> fill ();
return true;
}
};