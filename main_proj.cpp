#include "graph.hpp"
//#include "Labyrinthe.hpp"
using namespace std;
int main() {
    Graphe g(true); 

    
    g.ajouter_sommet(1);
    g.ajouter_sommet(2);
    g.ajouter_sommet(3);
    g.ajouter_sommet(4);
    // On a donc 1  2
    //           3  4

    g.ajouter_arete(1, 2);
    g.ajouter_arete(2, 3);
    g.ajouter_arete(3, 1);
    g.ajouter_arete(3, 4);

  
    unordered_set<int> voisins = g.voisins(3);
    cout << "Voisins de 3 : ";
    for (int v : voisins) {
        cout << v << " ";
    }
    cout << endl;

  
    bool existeArete = g.arete(1, 2);
    cout << "Il existe une arête entre 1 et 2 : " << (existeArete ? "Oui" : "Non") << endl;  //affiche non


    unordered_set<int> parcoursProf = g.parcours_prof(1);
    cout << "Parcours en profondeur à partir de 1 : ";// affiche  1 0
    for (int v : parcoursProf) {
        cout << v << " ";
    } 
    cout << endl;

 
    unordered_map<int, int> parcoursLarg = g.parcours_larg_chemin(1);
    cout << "Parcours en largeur à partir de 1 : " << endl;
    for (const auto& pair : parcoursLarg) {
        cout << pair.first << " : " << pair.second << endl;
    }/*Afiche  4 : 3
                3 : 2
                2 : 1
                1 : -1  //pb
*/

 
    vector<int> chemins = g.chemins(1, 4);
    cout << "Chemins entre 1 et 4 : "; //Chemins entre 1 et 4 : 0 
    for (int v : chemins) {
        cout << v << " ";
    }
    cout << endl;


    int distance = g.distance(1, 4);
    cout << "Distance entre 1 et 4 : " << distance << endl;  //affiche 3
    std::cout << g << std::endl;
    return 0;
}