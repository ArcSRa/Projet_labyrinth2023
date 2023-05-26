#include "graph.hpp"

//coins = [" ", "╶", "╵", "└", "╴", "─", "┘", "┴", "╷", "┌", "│", "├", "┐", "┬", "┤", "┼"]
static const vector<string> coins = { " ", "═", "║", "╚", "═", "═", "╝", "╩", "║", "╔", "║", "╠", "╗", "╦", "╣", "╬" };

class Labyrinthe: public Graphe {
    private:
    int w;
    int h;
    vector<vector<char>> repr;
    vector<pair<int, int>> ouvertures;
   
    public:

    Labyrinthe(int w = 0, int h = 0) : Graphe(false), w(w), h(h) {
    
        this->reset();
              //Tableau de la représentation du labyrinthe en mode semi-graphique
       // for(int c; c<2*this->h+1;c++){
     vector<vector<char>> repr(2 * h + 1, vector<char>(2 * w + 1, '*'));


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
   string construire_repr() {
        string resultat;
        // Les murs
        for (int c = 0; c < w; c++) {
            repr[0][2 * c + 1] = coins[5][0];
        }
        for (int l = 0; l < h; l++) {
            repr[2 * l + 1][0] = coins[10][0];
            for (int c = 0; c < w; c++) {
                if (l + 1 < h && arete(make_pair(l, c), make_pair(l + 1, c))) {
                    repr[2 * l + 2][2 * c + 1] = coins[0][0];
                } else {
                    repr[2 * l + 2][2 * c + 1] = coins[5][0];
                }

                if (c + 1 < w && arete(make_pair(l, c), make_pair(l, c + 1))) {
                    repr[2 * l + 1][2 * c + 2] = coins[0][0];
                } else {
                    repr[2 * l + 1][2 * c + 2] = coins[10][0];
                }
            }
        }

        // Les coins
        for (int l = 0; l < repr.size(); l += 2) {
            for (int c = 0; c < repr[0].size(); c += 2) {
                int code = 1 * (c + 1 < repr[0].size() && repr[l][c + 1] != ' ');
                code += 2 * ((l != 0) && (repr[l - 1][c] != ' '));
                code += 4 * (c != 0 && repr[l][c - 1] != ' ');
                code += 8 * (l + 1 < repr.size() && repr[l + 1][c] != ' ');
                repr[l][c] = coins[code][0];
            }
        }

        // Les ouvertures vers l'extérieur
        for (const auto& o : ouvertures) {
            int l = o.first;
            int c = o.second;
            if (c == 0) {
                repr[2 * l + 1][2 * c] = ' ';
            } else if (c == w - 1) {
                repr[2 * l + 1][2 * c + 2] = ' ';
            } else if (l == 0) {
                repr[2 * l][2 * c + 1] = ' ';
            } else if (l == h - 1) {
                repr[2 * l + 2][2 * c + 1] = ' ';
            }
        }

        for (const auto& row : repr) {
            for (char c : row) {
                resultat += c;
            }
            resultat += '\n';
        }

        return resultat;
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