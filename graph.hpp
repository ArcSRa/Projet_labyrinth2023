#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;
class Graphe {
private:
    unordered_map<int, unordered_set<int>> A;
    int w;
    int h;
    bool oriente;

public:
    Graphe(bool oriente = true) : oriente(oriente) {}

    void construire(unordered_map<int, unordered_set<int>> A) {
        this->w=0;
        this->h=0;
        this->A = A;
        for (auto& [x, V] : A) {
            this->w = std::max(this->w, x + 1);
            for (auto& y : V) {
                this->h = max(this->h, y + 1);
            }
        }
    }

    void ajouter_sommet(int x) {
        if (A.find(x) == A.end()) {
            A[x] = unordered_set<int>();
        }
    }

    void ajouter_arete(int x, int y) {
        ajouter_sommet(x);
        ajouter_sommet(y);
        A[x].insert(y);
        if (!oriente) {
            A[y].insert(x);
        }
    }

    unordered_set<int> voisins(int x) {
        return A[x];
    }

    vector<pair<int, int>> aretes() {
        vector<pair<int, int>> L;
        for (const auto& pair : A) {
            int x = pair.first;
            const unordered_set<int>& V = pair.second;
            for (int v : V) {
                L.push_back(make_pair(x, v));
            }
        }
        return L;
    }

    bool arete(int x, int y) {
        return A.find(y) != A.end() && A[y].find(x) != A[y].end();
    }

    unordered_set<int> parcours_prof(int s, unordered_set<int>& vus) {
        if (vus.find(s) == vus.end()) {
            vus.insert(s);
            for (int v : voisins(s)) {
                parcours_prof(v, vus);
            }
        }
        return vus;
    }

    unordered_map<int, int> parcours_ch(int s, int ori, unordered_map<int, int>& vus) {
        if (vus.find(s) == vus.end()) {
            vus[s] = ori;
            for (int v : voisins(s)) {
                parcours_ch(v, s, vus);
            }
        }
        return vus;
    }

    vector<int> chemins(int x, int y) {
        unordered_map<int, int> vus = parcours_ch(x, -1, vus);
        vector<int> c;
        if (vus.find(y) != vus.end()) {
            int s = y;
            while (s != -1) {
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

    unordered_map<int, int> parcours_larg(int s) {
        unordered_map<int, int> dist;
        unordered_set<int> cour;
        unordered_set<int> suiv;
        cour.insert(s);
        int d = 0;
        while (!cour.empty()) {
            int size = cour.size();
            for (int i = 0; i < size; i++) {
                int v = *cour.begin();
                cour.erase(cour.begin());
                dist[v] = d;
               // for (int
            }
        }
    }
};