#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;
using Tuple = tuple<int,int>;
using TupleSet = unordered_set<Tuple>;
using TupleMap = unordered_map<Tuple, TupleSet>;

class Graphe {
private:
    TupleMap A;
    int w;
    int h;
    bool oriente;

public:
    Graphe(bool oriente = true) : oriente(oriente) {}

    void construire(TupleMap A) {
        this->A=A;
        this->h=0;
        this->w=0;
        for (TupleMap::iterator it = A.begin(); it != A.end(); ++it) {
            const int& x = get<0>(it->first);
            const TupleSet& V = it->second;
            this->w = max(this->w, x + 1);
            for (Tuple y : V) {
                this->h = max(this->h, get<0>(y) + 1);
            }
        }
    }

    void ajouter_sommet(Tuple x) {
        if (this->A.find(x) == this->A.end()) {
            A[x] = TupleSet();
        }
    }

    void ajouter_arete(Tuple x, Tuple y) {
        ajouter_sommet(x);
        ajouter_sommet(y);
        this->A[x].insert(y);
        if (!oriente) {
            this->A[y].insert(x);
        }
    }

    TupleSet voisins(Tuple x) {
        return this->A[x];
    }

    TupleSet aretes() {
        TupleSet L;
        for (TupleMap::iterator it = this->A.begin(); it != this->A.end(); ++it) {
            const TupleSet& V = it->second;
            for (Tuple v : V) {
                L.push_back(v);
            }
        }
        return L;
    }
    // Antécédent : les sommets x et y existent, sinon on met un assert
    bool arete(Tuple x, Tuple y) {
        return this->A[y].find(x) != A[y].end();
    }

    TupleSet parcours_prof(Tuple s, TupleSet vus={}) {
        if (vus.find(s) == vus.end()) {
            vus.insert(s);
            for (Tuple v : voisins(s)) {
                parcours_prof(v, vus);
            }
        }
        return vus;
    }

    /*TupleMap parcours_ch(int s, int ori, TupleMap vus  = unordered_map<int, int>()) {
        if (vus.find(s) == vus.end()) {
            vus[s] = ori;
            for (int v : voisins(s)) {
                parcours_ch(v, s, vus);
            }
        }
        return vus;
    }*/

    vector<int> chemins(int x, int y) {
       
        unordered_map<int, int> vus =  this->parcours_ch(x,-1);
        vector<int> c={0};
        if (vus.find(y) != vus.end()) {
            int s = y;
            while (s != 0) {
                c.push_back(s);
                s = vus[s];
            }
        }
        reverse(c.begin(), c.end());
        return c;
    }
    

    bool existe_chemin(int x, int y) {
        unordered_set<int> vus;
        return parcours_prof(x, vus).find(y) != vus.end();
    }
//largeur
    std::unordered_map<int, int> parcours_larg(int s) {
        std::unordered_map<int, int> dist;
        std::unordered_set<int> cour;
        std::unordered_set<int> suiv;
        cour.insert(s);
        int d = 0;
        while (!cour.empty()) {
            int size = cour.size();
            for (int i = 0; i < size; i++) {
                int v = *cour.begin();
                cour.erase(cour.begin());
                dist[v] = d;
                for (int u : voisins(v)) {
                    if (dist.find(u) == dist.end()) {
                        suiv.insert(u);
                    }
                }
            }
            cour.swap(suiv);
            suiv.clear();
            d++;
        }
        return dist;
    }

    std::unordered_map<int, int> parcours_larg_chemin(int s) {
        std::unordered_map<int, int> vus;
        std::unordered_set<int> cour;
        std::unordered_set<int> suiv;
        cour.insert(s);
        vus[s] = -1;
        while (!cour.empty()) {
            int size = cour.size();
            for (int i = 0; i < size; i++) {
                int v = *cour.begin();
                cour.erase(cour.begin());
                for (int u : voisins(v)) {
                    if (vus.find(u) == vus.end()) {
                        suiv.insert(u);
                        vus[u] = v;
                    }
                }
            }
            cour.swap(suiv);
            suiv.clear();
        }
        return vus;
    }

    std::vector<int> chemins_larg(int x, int y) {
        std::unordered_map<int, int> vus = parcours_larg_chemin(x);
        std::vector<int> c;
        if (vus.find(y) != vus.end()) {
            int s = y;
            while (s != -1) {
                c.push_back(s);
                s = vus[s];
            }
        }
        std::reverse(c.begin(), c.end());
        return c;
    }

    int distance(Tuple x, Tuple y) {
        std::unordered_map<int, int> dist = parcours_larg(x);
        return (dist.find(y) != dist.end()) ? dist[y] : -1;
    }
};