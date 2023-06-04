#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
using cell = pair<int,int>;
using cellSet = set<cell>;
using cellMap = map<cell,cellSet>;
using Arete = pair<cell,cell>;
using Aretes = set<Arete>;

static constexpr cell None = make_pair(-1, -1);

class Graphe {
private:
    cellMap graph;
    int width;
    int height;
    bool oriented;

public:
    
    Graphe(int w, int h, bool oriented = true) : width(w), height(h), oriented(oriented) {}

    cellMap& getGraph(){
        return this->graph;
    }

    int getWidth(){
        return this->width;
    }

    int getHeight(){
        return this->height;
    }

    bool getOrient(){
        return this->oriented;
    }

    cellSet& getVoisins(cell x) {
        return this->graph[x];
    }

    void setGraph(cellMap map) {
        this->graph=map;
    }

    void setWidth(int w){
        this->width=w;
    }

    void setHeight(int h){
        this->height=h;
    }

    void setOrient(bool o){
        this->oriented=o;
    }

    void setVoisins(cell x, cellSet V) {
        this->graph[x]=V;
    }

    void insertVoisins(cell x, cell v){
        this->graph[x].insert(v);
    }

    void clearGraph() {
        this->graph.clear();
    }

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

    cellSet parcours_prof(cell s, cellSet& vus) {
        if (vus.find(s) == vus.end()) {
            vus.insert(s);
            for (cell v : getVoisins(s)) {
                parcours_prof(v, vus);
            }
        }
        return vus;
    }

    cellSet parcours_ch(cell s, cell ori, cellSet &vus) {
        if (vus.find(s) == vus.end()) {
            vus.insert(ori);
            for (cell v : getVoisins(s)) {
                parcours_ch(v, s, vus);
            }  
        }
        return vus;
    }

    cellSet chemins(cell x, cell y) {
        cell val1;
        cellSet val2;
        cellSet vus = this->parcours_ch(x,val1,val2);
        cellSet c=cellSet();
        if (vus.find(y) != vus.end()) {
            for (cellSet::iterator it=vus.begin();it!=vus.find(y);it++){
                c.insert(*it);
            }
        }
        return c;
    }
    
    bool existe_chemin(cell x, cell y) {
        cellSet val;
        cellSet vus = this->parcours_prof(x,val);
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