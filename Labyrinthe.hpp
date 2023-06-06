#include "graph.hpp"

//static const vector<string> coins = { " ", "═", "║", "╚", "═", "═", "╝", "╩", "║", "╔", "║", "╠", "╗", "╦", "╣", "╬" };
static const vector<string> coins = { " ", "-", "|", "L", "=", "=", "J", "I", "|", "P", "|", ">", "T", "^", "<", "+" };


class Labyrinthe: public Graphe {
    private:
        
        cellSet ouvertures;
   
    public:
        vector<vector<char>> repr;
        vector<vector<char>> getRepr() {
            return this->repr;
        }

        cellSet getOuvert() {
            return this->ouvertures;
        }

        void setRepr(vector<vector<char>> tab) {
            this->repr=tab;
        }

        void setRepr(int x, int y, char c){
            this->repr[x][y]=c;
        }

        void setOuvert(cellSet C) {
            this->ouvertures=C;
        }

        Labyrinthe(int w = 0, int h = 0) : Graphe(w,h,false) {
            reset();
            setRepr(vector<vector<char>>(2 * getHeight() + 1, vector<char>(2 * getWidth() + 1, ' ')));
            this->effacer_repr();
            this->ouvertures = cellSet();
        } 

        Labyrinthe(cellMap list) : Graphe(0,0,false){
            reset();
            construire(list);
            setRepr(vector<vector<char>>(2 * getHeight() + 1, vector<char>(2 * getWidth() + 1, ' ')));
            this->effacer_repr();
            this->ouvertures = cellSet();
        }

        void reset() {   
            clearGraph();
            for(int l=0; l<getHeight(); l++){
                for(int c=0; c<getWidth(); c++){
                    cell cellule(l,c);
                    this->ajouter_sommet(cellule);
                }
            }
        }

        void effacer_repr() {
            for(int l=0;l<getHeight();l++){
                for (int c=0;c<getWidth();c++){
                    setRepr(2*l+1,2*c+1,' ');
                }
            }
        }

        friend ostream& operator<<(ostream& os,  Labyrinthe& labyrinthe) {
            labyrinthe.construire_repr();
            for (const vector<char>& ligne : labyrinthe.getRepr()) {
                for (const char& cell : ligne) {
                    os << cell;
                }
                os << "\n";
            }
            return os;
        }

        string construire_repr() {
            string resultat;
            // Les murs
            for (int c = 0; c < getWidth(); c++) {
                repr[0][2 * c + 1] = coins[5][0];
                
            }
            for (int l = 0; l < getHeight(); l++) {
                repr[2 * l + 1][0] = coins[10][0];
                for (int c = 0; c < getWidth(); c++) {
                    if (l + 1 < getHeight() && arete(make_pair(l, c), make_pair(l + 1, c))) {
                        repr[2 * l + 2][2 * c + 1] = coins[0][0];
                    } else {
                        repr[2 * l + 2][2 * c + 1] = coins[5][0];
                    }

                    if (c + 1 < getWidth() && arete(make_pair(l, c), make_pair(l, c + 1))) {
                        repr[2 * l + 1][2 * c + 2] = coins[0][0];
                    } else {
                        repr[2 * l + 1][2 * c + 2] = coins[10][0]; //|
                    }
                }
            }

            //cout<<"coin"<<coins[1][0]<<endl;

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
                } else if (c == getWidth() - 1) {
                    repr[2 * l + 1][2 * c + 2] = ' ';
                } else if (l == 0) {
                    repr[2 * l][2 * c + 1] = ' ';
                } else if (l == getHeight() - 1) {
                    repr[2 * l + 2][2 * c + 1] = ' ';
                }
            }
        this->setRepr(1,1,'D');
        this->setRepr(repr.size()-2,repr[0].size()-2,'A');
            for (const auto& row : repr) {
                for (char c : row) {
                    resultat += c;
                }
                resultat += '\n';
            }

            return resultat;
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
                    if (i-1>=0) voisins.insert(haut);
                    if (j-1>=0) voisins.insert(gauche);
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
            for (cell c : voisins) murs.insert(make_pair(C,c));
            return murs;
        }
            
        cellSet voisins_cellule(cell C){
            return dic_adjac(this->getWidth(),this->getHeight())[C];
        }
            
        void ouvrir_passage(cell x, cell y) {
            cellSet test_x=voisins_cellule(x);
            //cellSet test_y=voisins_cellule(y);
            auto it = test_x.find(y);
                if (it != test_x.end()) {
                      this->ajouter_arete(x,y);
                    //  cout<<"Adjacent"<<endl;
             } 
                else {
                    // cout << "Pas adjacent" << endl;
             }
     
        }

 Aretes murs(int h, int w) {
            cellMap Dico = dic_adjac(h,w);
            Aretes m;
            for (cellMap::iterator it = Dico.begin(); it != Dico.end(); it++) {
                cell x = it->first;
                cellSet V = it->second;
                for (cell cell : V) {
                    m.insert(make_pair(x,cell));
                }
            }
            return m;
        }
   void construire_aldous_broder() {
    reset();
    //effacer_repr(); 
    cellSet visitees; 
    cell celluleCourante(0, 0); 
    visitees.insert(celluleCourante); 
    //this->setRepr(1,1,'G');
    int cellulesRestantes = this->getWidth() * this->getHeight() - 1; 
    set<Aretes> murs;
    //this->setRepr(1,1,'D');
    //this->setRepr(repr.size()-2,repr[0].size()-2,'A');
    while (cellulesRestantes > 0) {
        cellSet voisins = this->voisins_cellule(celluleCourante); 


        auto it = next(begin(voisins), rand() % voisins.size());
        cell voisin = *it;

        if (visitees.find(voisin) == visitees.end()) { 
            this->ouvrir_passage(celluleCourante,voisin);
         
            visitees.insert(voisin); 
            cellulesRestantes--; 
           
        }

        celluleCourante = voisin; 
   
      
    }
    
     
}
void construire_fusion() {
    reset();

    map<cell, int> values;
    int i = 0;

    for (pair<cell, cellSet> it : this->getGraph()) {
        values.insert(make_pair(it.first, i++));
    }

    Aretes m = murs(this->getHeight(), this->getWidth());

 

    while (!m.empty() ) {
        Aretes::iterator it = next(m.begin(), rand() % m.size());

        if (values[it->first] != values[it->second]) {
            this->ouvrir_passage(it->first, it->second);
            int temp = values[it->second];
            values[it->second] = values[it->first];

            for (auto& element : values) {
                if (element.second == temp) {
                    element.second = values[it->first];
                }
            }
        }

        m.erase(it);
     
    }
}

};