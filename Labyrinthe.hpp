#include "graph.hpp"
//
//coins = [" ", "╶", "╵", "└", "╴", "─", "┘", "┴", "╷", "┌", "│", "├", "┐", "┬", "┤", "┼"] //A voir pour les caractères qu'on utilisera
static const vector<string> coins = { " ", "═", "║", "╚", "═", "═", "╝", "╩", "║", "╔", "║", "╠", "╗", "╦", "╣", "╬" };

class Labyrinthe: public Graphe {
    private:
    int w;
    int h;
    cellMap A;
    vector<vector<char>> repr;
    vector<pair<int, int>> ouvertures;
   
    public:

    Labyrinthe(int w = 0, int h = 0) : Graphe(w,h,false), w(w), h(h) {
        A=Graphe::getGraph();
        this->reset();
              //Tableau de la représentation du labyrinthe en mode semi-graphique
       // for(int c; c<2*this->h+1;c++){
     vector<vector<char>> repr(2 * h + 1, vector<char>(2 * w + 1, '*'));


       // }
        this->effacer_repr();
        //Coordonnées des ouvertures vers l’extérieur
       this->ouvertures = vector<pair<int, int>>();
    } 
    Labyrinthe(int w,int h,cellMap list):Graphe(w,h,false), w(w), h(h),A(list){
      this->reset();
              //Tableau de la représentation du labyrinthe en mode semi-graphique
       
     vector<vector<char>> repr(2 * h + 1, vector<char>(2 * w + 1, '*'));


       // }
        this->effacer_repr();
        //Coordonnées des ouvertures vers l’extérieur
       this->ouvertures = vector<pair<int, int>>();

    }

    void reset() {   
        A.clear();
        for(int l=0;l<this->h;l++){
            for(int c=0;c<this->w;c++){
                cell coord(l,c);
                this->ajouter_sommet(coord);
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
        for (int c = 0; c < this->w; c++) {
            repr[0][2 * c + 1] = coins[5][0];
        }
        for (int l = 0; l < this->h; l++) {
            repr[2 * l + 1][0] = coins[10][0];
            for (int c = 0; c < this->w; c++) {
                if (l + 1 < this->h && arete(make_pair(l, c), make_pair(l + 1, c))) {
                    repr[2 * l + 2][2 * c + 1] = coins[0][0];
                } else {
                    repr[2 * l + 2][2 * c + 1] = coins[5][0];
                }

                if (c + 1 < this->w && arete(make_pair(l, c), make_pair(l, c + 1))) {
                    repr[2 * l + 1][2 * c + 2] = coins[0][0];
                } else {
                    repr[2 * l + 1][2 * c + 2] = coins[10][0];
                }
            }
        }

        // Les coins
        for (long unsigned int l = 0; l < repr.size(); l += 2) {
            for (long unsigned int c = 0; c < repr[0].size(); c += 2) {
                int code = 1 * (c + 1 < repr[0].size() && repr[l][c + 1] != ' ');
                code += 2 * ((l != 0) && (repr[l - 1][c] != ' '));
                code += 4 * (c != 0 && repr[l][c - 1] != ' ');
                code += 8 * (l + 1 < repr.size() && repr[l + 1][c] != ' ');
                repr[l][c] = coins[code][0];
            }
        }

        // Les ouvertures vers l'extérieur
        for (const auto& ouv : ouvertures) {
            int l = ouv.first;
            int c = ouv.second;
            if (c == 0) {
                repr[2 * l + 1][2 * c] = ' ';
            } else if (c == this->w - 1) {
                repr[2 * l + 1][2 * c + 2] = ' ';
            } else if (l == 0) {
                repr[2 * l][2 * c + 1] = ' ';
            } else if (l == this->h - 1) {
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

  cellMap dic_adjac(int w, int h) {
        cellMap Dico;
        for (int i=0; i<h; i++){
            for (int j=0; j<w; j++){
                cellSet voisins = cellSet();
                cell haut = make_pair(i-1,j);
                cell gauche = make_pair(i,j-1);
                cell bas = make_pair(i+1,j);
                cell droite = make_pair(i,j+1);
                if (i-1>0) voisins.insert(haut);
                if (j-1>0) voisins.insert(gauche);
                if (i+1<h) voisins.insert(bas);
                if (j+1<w) voisins.insert(droite);
                Dico[make_pair(i,j)]=voisins;
            }
        }
        return Dico;
    }
    
    Aretes murs_cellule(cell C) {
        Aretes murs;
        cellSet voisins = voisins_cellule(C);
        for (cell c : voisins) murs.insert(C,c);
        return murs;
    }
        
    cellSet voisins_cellule(cell C){
        return dic_adjac(this->getWidth(),this->getHeight())[C];
    }
        
    void ouvrir_passage(cell x, cell y) {
        this->ajouter_arete(x,y);
    }
};