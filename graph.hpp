#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

//
using namespace std;
using cell = pair<int,int>;
using cellSet = set<cell>;
using cellMap = map<cell,cellSet>;
using Arete = pair<cell,cell>;

static constexpr cell None = make_pair(-1, -1);

class Graphe {
private:
    cellMap graph;
    int width;
    int height;
    bool oriented;

public:
    
    Graphe(int w, int h, bool oriented = true) : width(w), height(h), oriented(oriented) {}

    cellMap getGraph(){
        return this->graph;
    }

    void construire(cellMap graph) {
        this->graph=graph;
        this->height=0;
        this->width=0;
        int x,y;
        for (cellMap::iterator it = graph.begin(); it != graph.end(); it++) {
            x = get<0>(it->first);
            this->width = max(this->width, x + 1);
            y = get<1>(it->first);
            this->height = max(this->height, y + 1);
        }
    }

    void ajouter_sommet(cell x) {
        if (this->graph.find(x) == this->graph.end()) {
            this->graph[x] = {};
        }
    }

    void ajouter_arete(cell x, cell y) {
        this->ajouter_sommet(x);
        this->ajouter_sommet(y);
        this->graph[x].insert(y);
        if (!oriented) {
            this->graph[y].insert(x);
        }
    }

    cellSet voisins(cell x) {
        return this->graph[x];
    }

    vector<Arete> aretes() {
        vector<Arete> L;
        for (cellMap::iterator it = this->graph.begin(); it != this->graph.end(); it++) {
            cell x = it->first;
            cellSet V = it->second;
            for (cell cell : V) {
                L.push_back(make_pair(x,cell));
            }
        }
        return L;
    }
    
    // Antécédent : les sommets x et y existent, sinon on met un assert
    bool arete(cell x, cell y) {
        return this->graph[y].find(x) != this->graph[y].end();
    }

    cellSet parcours_prof(cell s, cellSet vus=cellSet()) {
        if (vus.find(s) == vus.end()) {
            vus.insert(s);
            for (cell v : this->voisins(s)) {
                parcours_prof(v, vus);
            }
        }
        return vus;
    }

    cellSet parcours_ch(cell s, cell ori=None, cellSet vus=cellSet({None})) {
        if (vus.find(s) == vus.end()) {
            vus.insert(ori);
            for (cell v : voisins(s)) {
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
        //reverse(c.begin(), c.end());
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
            for (cell v : voisins(temp)) {
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
            for (cell v : voisins(temp)) {
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
        //reverse(c.begin(), c.end());
        return c;
    }

    int distance(cell x, cell y) {
        map<cell,int> dist = this->parcours_larg(x);
        return (dist.find(y)!=dist.end())?dist[y]:-1;
    }
};