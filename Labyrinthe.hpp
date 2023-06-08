#include "graph.hpp"
#include <queue>
//static const vector<string> coins = { " ", "═", "║", "╚", "═", "═", "╝", "╩", "║", "╔", "║", "╠", "╗", "╦", "╣", "╬" };
static const vector<string> coins = { " ", "-", "|", "L", "=", "=", "J", "I", "|", "P", "|", ">", "T", "^", "<", "+" };


class Labyrinthe: public Graphe {
    private:
        int height;
        int width;
        cellSet ouvertures;
   
    public:
        vector<vector<char>> repr;
        /* Rôle : Retourne la représentation de l'objet courant
         * Antécédent : L'objet courant doit être construit
        */
        vector<vector<char>> getRepr() {
            return this->repr;
        }
        /* Rôle : Retourne la liste des ouvertures de l'objet courant
         * Antécédent : L'objet courant doit être construit
         */
        cellSet getOuvert() {
            return this->ouvertures;
        }
        /* Rôle : Modifie la représentation entière de l'objet courant
         * Antécédent : L'objet courant doit être construit
         */
        void setRepr(vector<vector<char>> tab) {
            this->repr=tab;
        }
        /* Rôle : Modifie un caractère de la représentation de l'objet courant
         * Antécédent : L'objet courant doit être construit
         */
        void setRepr(int x, int y, char c){
            this->repr[x][y]=c;
        }
        /* Rôle : Modifie la liste des ouvertures de l'objet courant
         * Antécédent : L'objet courant doit être construit
         */
        void setOuvert(cellSet C) {
            this->ouvertures=C;
        }
        // Constructeur de la classe Labyrinthe
        Labyrinthe(int w = 0, int h = 0) : Graphe(w,h,false) {
            reset();
            width=getWidth();
            height=getHeight();
            setRepr(vector<vector<char>>(2 * getHeight() + 1, vector<char>(2 * getWidth() + 1, ' ')));
            this->effacer_repr();
            this->ouvertures = cellSet();
        } 
        // Second constructeur de la classe Labyrinthe
        Labyrinthe(cellMap list) : Graphe(0,0,false){
            reset();
            construire(list);
            setRepr(vector<vector<char>>(2 * getHeight() + 1, vector<char>(2 * getWidth() + 1, ' ')));
            this->effacer_repr();
            this->ouvertures = cellSet();
        }
        /* Rôle : Permet de réinitialiser le graph d'un Labyrinthe
         * Antécédent : L'objet courant doit être construit
         * Conséquent : Le graph ne contient plus que des cellules non liées
         */
        void reset() {   
            clearGraph();
            for(int l=0; l<getHeight(); l++){
                for(int c=0; c<getWidth(); c++){
                    cell cellule(l,c);
                    this->ajouter_sommet(cellule);
                }
            }
        }
        /* Rôle : Permet de remplacer certains caractères de la représentation par des espaces  
         * Antécédent : L'objet courant doit être construit
         * Conséquent : La représentation du Labyrinthe est modifiée
         */
        void effacer_repr() {
            for(int l=0;l<getHeight();l++){
                for (int c=0;c<getWidth();c++){
                    setRepr(2*l+1,2*c+1,' ');
                }
            }
        }
        /* Rôle : Permet d'adapter l'objet Labyrinthe avec l'opérateur '<<'
         * Antécédent : L'objet courant doit être construit
         * Conséquent : Affiche sur la sortie standard le graph d'un Labyrinthe
         */
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

        /* Rôle : Génère une représentation en chaîne de caractères du graph du Labyrinthe courant
         * Antécédent : L'objet courant doit être construit
         * Conséquent : Retourne une chaine de caractères de la représentation du Labyrinthe
         */
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
        /* Rôle : Permet d'obtenir un dictionnaire d'adjacence selon la taille d'un Labyrinthe
         * Antécédent : La hauteur et la longueur doivent être fournis
         * Conséquent : Retourne une cellMap contenant toutes les pair<cell,cellSet> avec chaque
         * cellule du Labyrinthe et ses voisins potentiels
         */
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
        /* Rôle : Permet d'obtenir tous les murs d'une cellule passée en paramètre
         * Antécédent : L'objet doit être construit
         * Conséquent : Retourne un set d'Arete contenant les murs de la cellule
         */
        Aretes murs_cellule(cell C) {
            Aretes murs;
            cellSet voisins = voisins_cellule(C);
            for (cell c : voisins) murs.insert(make_pair(C,c));
            return murs;
        }
        /* Rôle : Permet d'obtenir les voisins d'une cellule passée en paramètre
         * Antécédent : L'objet doit être construit
         * Conséquent : Retourne un set des cellules voisines
         */   
        cellSet voisins_cellule(cell C){
            return dic_adjac(this->getWidth(),this->getHeight())[C];
        }

        /* Rôle : Permet d'ouvrir le passage entre deux cellules dans un Labyrinthe
         * Antécédent : L'objet doit être construit
         * Conséquent : Ajoute une arête dans le graph du Labyrinthe
         */   
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

        /* Rôle : Permet d'obtenir tous les murs d'un Labyrinthe
         * Antécédent : La hauteur et la longueur doivent être fournis
         * Conséquent : Retourne un set d'Arete contenant tous les murs
         */ 
        Aretes murs(int h, int w) {
            Aretes m;

            for (int l = 0; l < h; l++) {
                for (int c = 0; c < w; c++) {
                    cell cellule(l, c);

                    // Vérifier la présence de voisins à droite et en bas
                    if (c + 1 < w) {
                        cell voisinDroite(l, c+1);
                        m.insert(make_pair(cellule, voisinDroite));
                    }
                    if (l + 1 < h) {
                        cell voisinBas(l+1, c);
                        m.insert(make_pair(cellule, voisinBas));
                    }
                }
            }

            return m;
        }
        /* Rôle : Permet de construire un Labyrinthe selon l'algorithme Aldous Broder
         * Antécédent : L'objet doit être construit
         * Conséquent : Retourne une représentation de ce nouveau labyrinthe
         */ 
   void construire_aldous_broder() {
    reset();
   
    cellSet visitees; 
    cell celluleCourante(0, 0); 
    visitees.insert(celluleCourante); 
   
    int cellulesRestantes = this->getWidth() * this->getHeight() - 1; 

  
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

        /* Rôle : Permet de construire un Labyrinthe selon l'algorithme Fusion
         * Antécédent : L'objet doit être construit
         * Conséquent : Retourne une représentation de ce nouveau labyrinthe
         */ 
        void construire_fusion() {
            reset();

            map<cell, int> values;
            int i = 0;

            for (pair<cell, cellSet> it : this->getGraph()) {
                values.insert(make_pair(it.first, i++));
            }

            Aretes m = murs(this->getHeight(), this->getWidth());

            while (!m.empty()) {
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
        /* Rôle : Permet de calculer la solution du labyrinthe
         * Antécédent : L'objet doit être construit
         * Conséquent : Renvoie le chemin/solution le plus rapide à la sortie
         */ 
        vector<cell> bfs(const Labyrinthe& labyrinthe, const cell& start, const cell& goal) {
            vector<cell> path;

        
            // Tableau pour garder la trace des cellules visitées
            map<cell, cell> parent;
            parent[start] = start;

            // File d'attente pour le parcours BFS
            queue<cell> q;
            q.push(start);

            bool path_found = false;

            while (!q.empty()) {
                cell current = q.front();
                q.pop();

                // Si on atteint la cellule objectif, construire le chemin
                if (current == goal) {
                    path_found = true;
                    break;
                }

                // Parcourir les voisins de la cellule actuelle
                for (const auto& neighbor : this->voisins_cellule(current)) {
                    if (!parent.count(neighbor) && this->arete(neighbor,current)) {
                        q.push(neighbor);
                        parent[neighbor] = current;
                    }
                }
            }

            // Construire le chemin si trouvé
            if (path_found) {
                cell current = goal;
                while (current != start) {
                    path.push_back(current);
                    current = parent[current];
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
            } else {
                cout << "Path not found." << endl;
            }

            return path;
        }
};