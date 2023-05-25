#include "graph.hpp"

//coins = [" ", "╶", "╵", "└", "╴", "─", "┘", "┴", "╷", "┌", "│", "├", "┐", "┬", "┤", "┼"]
static const vector<string> coins = { " ", "═", "║", "╚", "═", "═", "╝", "╩", "║", "╔", "║", "╠", "╗", "╦", "╣", "╬" };

class Labyrinthe: public Graphe {
    private:
    int w;
    int h;
    vector<vector<string>> repr;
    vector<pair<int, int>> ouvertures;
   
    public:

    Labyrinthe(int w = 0, int h = 0) : Graphe(false), w(w), h(h) {
    
        this->reset();
              //Tableau de la représentation du labyrinthe en mode semi-graphique
       // for(int c; c<2*this->h+1;c++){
     std::vector<std::vector<char>> repr(2 * h + 1, std::vector<char>(2 * w + 1, '*'));


       // }
        this->effacer_repr();
        //Coordonnées des ouvertures vers l’extérieur
       this->ouvertures = vector<pair<int, int>>();
    } 
    

    void reset()
    {   
        A.clear();
    for(int l=0;l<this->h;l++){
        for(int c=0;c<this->w;c++)
            {this->ajouter_sommet((l,c));}

    }
    }
    // void ToString(){
    //     this->construire_repr();
    //     string s;
    //     for(auto& l:this->repr)
    //     {
    //         s.append(''+l);
    //     }
    //}
      friend ostream& operator<<(ostream& os,  Labyrinthe& labyrinthe) {
        labyrinthe.construire_repr();
        for (const auto& ligne : labyrinthe.repr) {
            for (const auto& cell : ligne) {
                os << cell;
            }
            os << "\n";
        }
        return os;
    }
    void construire_repr()
    {//murs
        for(int c=0;c<this->w;c++)
            {
                this->repr[0][2*c+1]=coins[5];
            }
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