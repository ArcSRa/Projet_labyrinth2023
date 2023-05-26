#pragma once
#include <gtkmm.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "grille.hpp"
using namespace std;
class Vue:public Gtk::Window{
private:
    Gtk::Box box;
    Gtk::Button bClose;
    Gtk::Button Permu;
    Gtk::Image img;
    const  vector<string> tab={"Gtk_im.jpeg","img2.png"};
 

public:
    Vue():box(Gtk::ORIENTATION_VERTICAL),bClose("Close"),img(tab.front() ),Permu("Permuter")
    {   img.set(tab.front());
        box.pack_start(img);
        box.pack_start(bClose);
          box.pack_start(Permu);
        add(box);
        show_all_children();
    bClose . signal_clicked (). connect ( sigc :: mem_fun (* this , & Vue :: close ));
    Permu. signal_clicked (). connect ( sigc :: mem_fun (* this , & Vue :: permut ));
    }
void close () { Gtk :: Window :: close (); }
void permut () {
    static bool t=true;
 
   this->img.set(t ? tab.back():tab.front());
  t=!t;
 
 }
    virtual ~Vue() {}

};


class VueG:public Gtk::Window{
private:
    Gtk::Box box;
    Gtk::Button bClose;
    Gtk::Image img;
    Grille grille;
public:
    VueG():box(Gtk::ORIENTATION_VERTICAL),bClose("Close")
    {  
       
      
       box.pack_start(grille);
           box.pack_start(bClose);
        add(box);
        
         show_all_children();
        bClose . signal_clicked (). connect ( sigc :: mem_fun (* this , & VueG :: close ));

    }

void close () { Gtk :: Window :: close (); }
    virtual ~VueG() {}

};