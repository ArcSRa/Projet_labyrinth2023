#include <iostream>
//#include <unordered_map>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>


using namespace std;
using Tuple = tuple<int,int>;
using TupleSet = set<Tuple>;
using TupleMap = map<Tuple,TupleSet>;
using Arete = pair<Tuple,Tuple>;

//using TupleSet = unordered_set<Tuple>;
//using TupleMap = unordered_map<Tuple, TupleSet>;
//using DicoMap = unordered_map<Tuple, Tuple>;

class Graphe {
private:
    TupleMap graph;
    int width;
    int height;
    bool oriented;

public:
    static constexpr Tuple None = make_tuple(-1, -1);
    Graphe(int w, int h, bool oriented = true) : width(w), height(h), oriented(oriented) {}

    TupleMap getGraph(){
        return this->graph;
    }

    void construire(TupleMap graph) {
        this->graph=graph;
        this->height=0;
        this->width=0;
        int x,y;
        for (TupleMap::iterator it = graph.begin(); it != graph.end(); it++) {
            x = get<0>(it->first);
            this->width = max(this->width, x + 1);
            y = get<1>(it->first);
            this->height = max(this->height, y + 1);
            //const TupleVect& V = it->second;
            //for (Tuple y : V) {
            //    this->h = max(this->h, get<0>(y) + 1);
            //}
        }
    }

    void ajouter_sommet(Tuple x) {
        if (this->graph.find(x) == this->graph.end()) {
            this->graph[x] = {};
        }
    }

    void ajouter_arete(Tuple x, Tuple y) {
        this->ajouter_sommet(x);
        this->ajouter_sommet(y);
        this->graph[x].insert(y);
        if (!oriented) {
            this->graph[y].insert(x);
        }
    }

    TupleSet voisins(Tuple x) {
        return this->graph[x];
    }

    vector<Arete> aretes() {
        vector<Arete> L;
        for (TupleMap::iterator it = this->graph.begin(); it != this->graph.end(); it++) {
            Tuple x = it->first;
            TupleSet V = it->second;
            for (Tuple cell : V) {
                L.push_back(make_pair(x,cell));
            }
        }
        return L;
    }
    
    // Antécédent : les sommets x et y existent, sinon on met un assert
    bool arete(Tuple x, Tuple y) {
        return this->graph[y].find(x) != this->graph[y].end();
    }

    TupleSet parcours_prof(Tuple s, TupleSet vus=TupleSet({None})) {
        if (vus.find(s) == vus.end()) {
            vus.insert(s);
            for (Tuple v : this->voisins(s)) {
                parcours_prof(v, vus);
            }
        }
        return vus;
    }

    TupleSet parcours_ch(Tuple s, Tuple ori=None, TupleSet vus=TupleSet({None})) {
        if (vus.find(s) == vus.end()) {
            vus.insert(ori);
            for (Tuple v : voisins(s)) {
                parcours_ch(v, s, vus);
            }  
        }
        return vus;
    }

    TupleSet chemins(Tuple x, Tuple y) {
        TupleSet vus = this->parcours_ch(x);
        TupleSet c=TupleSet({});
        if (vus.find(y) != vus.end()) {
            for (TupleSet::iterator it=vus.begin();it!=vus.find(y);it++){
                c.insert(*it);
            }
        }
        //reverse(c.begin(), c.end());
        return c;
    }
    
    bool existe_chemin(Tuple x, Tuple y) {
        TupleSet vus = this->parcours_prof(x);
        return vus.find(y) != vus.end();
    }

    map<Tuple,int> parcours_larg(Tuple s) {
        map<Tuple,int> dist = {{s,0}};
        TupleSet cour = {s};
        TupleSet suiv = TupleSet({});
        while (!cour.empty()) {
            Tuple temp = *cour.begin();
            cour.erase(s);
            for (Tuple v : voisins(temp)) {
                if (dist.find(v) == dist.end()) {
                    suiv.insert(v);
                    dist[v]=dist[s]+1;
                }
            }
            if (cour.empty()) {
                cour=suiv;
                suiv = TupleSet({});
            }
        }
        return dist;
    }

    TupleSet parcours_larg_chemin(Tuple s) {
        TupleSet vus = TupleSet({None});
        TupleSet cour = {s};
        TupleSet suiv = TupleSet({});
        while (!cour.empty()) {
            Tuple temp = *cour.begin();
            cour.erase(s);
            for (Tuple v : voisins(temp)) {
                if (vus.find(v) == vus.end()) {
                    suiv.insert(v);
                    vus.insert(temp); // Warning
                }
            }
            if (cour.empty()) {
                cour=suiv;
                suiv = TupleSet({});
            }
        }
        return vus;
    }

    TupleSet chemins_larg(Tuple x, Tuple y) {
        TupleSet vus = parcours_larg_chemin(x);
        TupleSet c=TupleSet({});
        if (vus.find(y) != vus.end()) {
            for (TupleSet::iterator it=vus.begin();it!=vus.find(y);it++){
                c.insert(*it);
            }
        }
        //reverse(c.begin(), c.end());
        return c;
    }

    int distance(Tuple x, Tuple y) {
        map<Tuple,int> dist = this->parcours_larg(x);
        return (dist.find(y)!=dist.end())?dist[y]:-1;
    }
};