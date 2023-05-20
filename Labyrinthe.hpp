#include "graph.hpp"

//coins = [" ", "╶", "╵", "└", "╴", "─", "┘", "┴", "╷", "┌", "│", "├", "┐", "┬", "┤", "┼"]

class Labyrinthe: public Graphe {
    private:
    int w;
    int h;
    vector<vector<char>> repr;
    vector<pair<int, int>> ouvertures;

    static const vector<char> coins;
    public:

    Labyrinthe(int w = 0, int h = 0) : Graphe(false), w(w), h(h) {
    
        this->reset();
              //Tableau de la représentation du labyrinthe en mode semi-graphique
        repr = vector<vector<char>>(2 * h + 1, vector<char>(2 * w + 1, '*'));
        this->effacer_repr();
        //Coordonnées des ouvertures vers l’extérieur
       // this->ouvertures = [];
    } 

    void reset()
    {

    }

    void construire_repr()
    {
        
    }

    void effacer_repr()
    {//const char vide=' ';
        for(int l=0;l<this->h;l++)
        {
            for (int c=0;c<this->w;c++){
                this->repr[2*l+1][2*c+1] = ' ';
            }
        }

    }







};