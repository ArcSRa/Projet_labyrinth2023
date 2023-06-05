#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

/* Création d'alias pour raccourcir les types utilisés :
 *
 * cell : correspond à une cellule représenté par une paire d'entiers correspondant 
 * aux coordonnées (ligne,colonne) de la cellule
 * 
 * cellSet : correspond à une liste de cellules représenté par un set de cell (cellule)
 * 
 * cellMap : correspond à un graph de cellules avec les cellules voisines représentés par 
 * une map dont les clés sont des cell (cellule) et les valeurs sont des cellSet (liste de cell)
 * 
 * Arete : correspond à une arête dans un graphe représenté par une paire de cell (cellule)
 * 
 * Aretes : correspond à un ensemble d'arêtes représenté par un set d'Arete
 */
using cell = pair<int,int>;
using cellSet = set<cell>;
using cellMap = map<cell,cellSet>;
using Arete = pair<cell,cell>;
using Aretes = set<Arete>;

static constexpr cell None = make_pair(-1, -1);

class Graphe {
private:
    /* Attributs privés de la classe Graphe :
     * graph : correspond à la représentation sous forme d'une cellMap d'un graphe

     * width : correspond à la taille en longueur d'un graphe

     * height : correspond à la taille en hauteur d'un graphe

     * oriented : correspond à l'orientation des arêtes d'un graphe.
     *    à false : le graphe n'est pas orienté, donc on peut circuler dans les deux sens 
     *    entre deux cellules liées
     *    à true : le graphe est orienté, donc le passage d'une cellule à une autre 
     *    n'implique pas nécessairement un passage dans le sens inverse
     */
    cellMap graph;
    int width;
    int height;
    bool oriented;

public:

    //Constructeur de la classe Graphe
    Graphe(int w, int h, bool oriented = true) : width(w), height(h), oriented(oriented) {}

    /* Rôle : Retourne la cellMap graph de l'objet courant
     * Antécédent : L'objet courant doit être construit
     */
    cellMap& getGraph(){
        return this->graph;
    }

    /* Rôle : Retourne la taille en longueur de l'objet courant
     * Antécédent : L'objet courant doit être construit
     */
    int getWidth(){
        return this->width;
    }

    /* Rôle : Retourne la taille en hauteur de l'objet courant
     * Antécédent : L'objet courant doit être construit
     */
    int getHeight(){
        return this->height;
    }

    /* Rôle : Retourne la valeur booléenne de l'orientation de l'objet courant
     * Antécédent : L'objet courant doit être construit
     */
    bool getOrient(){
        return this->oriented;
    }

    /* Rôle : Retourne la liste des voisins accessibles en partant de la cellule x de l'objet courant
     * Antécédent : L'objet courant doit être construit
     */
    cellSet& getVoisins(cell x) {
        return this->graph[x];
    }

    /* Rôle : Modifie la cellMap graph de l'objet courant par celle passée en paramètre
     * Antécédent : L'objet courant doit être construit
     */
    void setGraph(cellMap map) {
        this->graph=map;
    }

    /* Rôle : Modifie la taille en longueur de l'objet courant par celle passée en paramètre
     * Antécédent : L'objet courant doit être construit
     */
    void setWidth(int w){
        this->width=w;
    }

    /* Rôle : Modifie la taille en hauteur de l'objet courant par celle passée en paramètre
     * Antécédent : L'objet courant doit être construit
     */
    void setHeight(int h){
        this->height=h;
    }

    /* Rôle : Modifie la valeur booléenne de l'orientation de l'objet courant par celle passée en paramètre
     * Antécédent : L'objet courant doit être construit
     */
    void setOrient(bool o){
        this->oriented=o;
    }

    /* Rôle : Modifie la liste des voisins accessibles en partant de la cellule x de l'objet courant 
     * par celle passée en paramètre
     * Antécédent : L'objet courant doit être construit
     */
    void setVoisins(cell x, cellSet V) {
        this->graph[x]=V;
    }

    /* Rôle : Modifie la liste des voisins accessibles en partant de la cellule x de l'objet courant 
     * en y ajoutant uniquement une cellule voisine
     * Antécédent : L'objet courant doit être construit
     */
    void insertVoisins(cell x, cell v){
        this->graph[x].insert(v);
    }

    /* Rôle : Supprime tous les éléments de la cellMap graph de l'objet courant
     * Antécédent : L'objet courant doit être construit
     */
    void clearGraph() {
        this->graph.clear();
    }

    /* Rôle : Reconstruit l'objet Graphe courant à partir d'une cellMap passée en paramètre
       Antécédent : L'objet courant doit être construit
       Conséquent : 
    */
    void construire(cellMap graph) {
        setGraph(graph);
        setWidth(0);
        setHeight(0);
        int x,y;
        for (cellMap::iterator it = graph.begin(); it != graph.end(); it++) {
            x = get<0>(it->first);
            setWidth(max(getWidth(), x + 1));
            y = get<1>(it->first);
            setHeight(max(getHeight(), y + 1));
        }
    }

    void ajouter_sommet(cell x) {
        if (getGraph().find(x) == getGraph().end()) {
            setVoisins(x,{});
        }
    }

    void ajouter_arete(cell x, cell y) {
        this->ajouter_sommet(x);
        this->ajouter_sommet(y);
        insertVoisins(x,y);
        if (!oriented) {
            insertVoisins(y,x);
        }
    }

    Aretes aretes() {
        Aretes L;
        for (cellMap::iterator it = getGraph().begin(); it != getGraph().end(); it++) {
            cell x = it->first;
            cellSet V = it->second;
            for (cell cell : V) {
                L.insert(make_pair(x,cell));
            }
        }
        return L;
    }
    
    // Antécédent : les sommets x et y existent, sinon on met un assert
    bool arete(cell x, cell y) {
        return getVoisins(y).find(x) != getVoisins(y).end();
    }

    cellSet parcours_prof(cell s, cellSet vus=cellSet()) {
        if (vus.find(s) == vus.end()) {
            vus.insert(s);
            for (cell v : getVoisins(s)) {
                parcours_prof(v, vus);
            }
        }
        return vus;
    }

    cellSet parcours_ch(cell s, cell ori=None, cellSet vus=cellSet({None})) {
        if (vus.find(s) == vus.end()) {
            vus.insert(ori);
            for (cell v : getVoisins(s)) {
                parcours_ch(v, s, vus);
            }  
        }
        return vus;
    }

    cellSet chemins(cell x, cell y) {
        cellSet vus = this->parcours_ch(x);
        cellSet c=cellSet();
        if (vus.find(y) != vus.end()) {
            for (cellSet::iterator it=vus.begin();it!=vus.find(y);it++){
                c.insert(*it);
            }
        }
        return c;
    }
    
    bool existe_chemin(cell x, cell y) {
        cellSet vus = this->parcours_prof(x);
        return vus.find(y) != vus.end();
    }

    map<cell,int> parcours_larg(cell s) {
        map<cell,int> dist = {{s,0}};
        cellSet cour = {s};
        cellSet suiv = cellSet({});
        while (!cour.empty()) {
            cell temp = *cour.begin();
            cour.erase(s);
            for (cell v : getVoisins(temp)) {
                if (dist.find(v) == dist.end()) {
                    suiv.insert(v);
                    dist[v]=dist[s]+1;
                }
            }
            if (cour.empty()) {
                cour=suiv;
                suiv = cellSet({});
            }
        }
        return dist;
    }

    cellSet parcours_larg_chemin(cell s) {
        cellSet vus = cellSet({None});
        cellSet cour = {s};
        cellSet suiv = cellSet({});
        while (!cour.empty()) {
            cell temp = *cour.begin();
            cour.erase(s);
            for (cell v : getVoisins(temp)) {
                if (vus.find(v) == vus.end()) {
                    suiv.insert(v);
                    vus.insert(temp); // Warning
                }
            }
            if (cour.empty()) {
                cour=suiv;
                suiv = cellSet({});
            }
        }
        return vus;
    }

    cellSet chemins_larg(cell x, cell y) {
        cellSet vus = parcours_larg_chemin(x);
        cellSet c=cellSet({});
        if (vus.find(y) != vus.end()) {
            for (cellSet::iterator it=vus.begin();it!=vus.find(y);it++){
                c.insert(*it);
            }
        }
        return c;
    }

    int distance(cell x, cell y) {
        map<cell,int> dist = this->parcours_larg(x);
        return (dist.find(y)!=dist.end())?dist[y]:-1;
    }
};