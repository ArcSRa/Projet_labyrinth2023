#include "graph.hpp"

//coins = [" ", "╶", "╵", "└", "╴", "─", "┘", "┴", "╷", "┌", "│", "├", "┐", "┬", "┤", "┼"]
using namespace std;

class Labyrinth : private Graphe{
    private:
        vector<vector<char>> repr;
        vector<pair<int, int>> ouvertures;
    public :
    Labyrinth(int w = 0, int h = 0) : Graphe(w,h,false) {
    
        this->reset();
        //Tableau de la représentation du labyrinthe en mode semi-graphique
        // for(int c; c<2*this->h+1;c++){
        this->repr = vector<vector<char>>(2 * this->h + 1, vector<char>(2*this->w + 1, '*'));
        // }
        this->effacer_repr();
        //Coordonnées des ouvertures vers l’extérieur
        this->ouvertures = vector<pair<int, int>>();
    }

    void reset() {   
        this->A.clear();
        for(int l=0;l<this->h;l++){
            for(int c=0;c<this->w;c++){
                this->ajouter_sommet((l,c));
            }
        }
    } 

    // void ToString(){
    //     this->construire_repr();
    //     string s;
    //     for(auto& l:this->repr)
    //     {
    //         s.append(''+l);
    //     }
    // }

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

    void construire_repr() {//murs
        int c,l;
        for(c=0;c<this->w;c++) {
            this->repr[0][2*c+1]=coins[5];
        }
        for(l=0;l<this->h;l++) {
            this->repr[2*l+1][0]=coins[10];
        }
        for(c=0;c<this->w;c++) {
            if l+1 < this->h and this.arete((l, c), (l+1, c)):
                    self.repr[2*l+2][2*c+1] = Labyrinthe.coins[0]
                else:
                    self.repr[2*l+2][2*c+1] = Labyrinthe.coins[5]
                if c+1 < self.w and self.arete((l, c), (l, c+1)):
                    self.repr[2*l+1][2*c+2] = Labyrinthe.coins[0]
                else:
                    self.repr[2*l+1][2*c+2] = Labyrinthe.coins[10]
        }
    }

    void effacer_repr() {//const char vide=' ';
        for(int l=0;l<this->h;l++) {
            for (int c=0;c<this->w;c++){
                this->repr[2*l+1][2*c+1] = ' ';
            }
        }
    }

    unordered_map<pair<int,int>,unordered_set<int>> dic_adjac(int w, int h) {
    }
    
    vector<pair<int,int>> murs_cellule(int cell)
        vector<pair<int,int>> coins=Graphe.aretes();
        for (const pair& coin : coins) {
            if (coin.first != cell || coin.second != cell) {
                coins.erase(coin);
            }
        }
    unordered_set<int> voisins_cellule(int cell)
        
    void ouvrir_passage(x, y)
        Graphe.ajouter_arete









};