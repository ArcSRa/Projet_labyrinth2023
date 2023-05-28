//#include "graph.hpp"
#include "Labyrinthe.hpp"
int main() {
cellMap graph ={
    {make_pair(0, 0), {make_pair(0, 1), make_pair(1, 0)}},
    {make_pair(0, 1), {make_pair(0, 0), make_pair(1, 1)}},
    {make_pair(0, 2), {make_pair(1, 2), make_pair(0, 3)}},
    {make_pair(0, 3), {make_pair(0, 2), make_pair(1, 3)}},
    {make_pair(1, 0), {make_pair(0, 0), make_pair(2, 0)}},
    {make_pair(1, 1), {make_pair(0, 1), make_pair(1, 2)}},
    {make_pair(1, 2), {make_pair(1, 1), make_pair(0, 2)}},
    {make_pair(1, 3), {make_pair(0, 3), make_pair(2, 3)}},
    {make_pair(2, 0), {make_pair(1, 0), make_pair(2, 1)}},
    {make_pair(2, 1), {make_pair(2, 0)}},
    {make_pair(2, 2), {make_pair(2, 3), make_pair(3, 2)}},
    {make_pair(2, 3), {make_pair(1, 3), make_pair(2, 2), make_pair(3, 3)}},
    {make_pair(3, 0), {make_pair(3, 1), make_pair(4, 0)}},
    {make_pair(3, 1), {make_pair(3, 0), make_pair(3, 2)}},
    {make_pair(3, 2), {make_pair(3, 1), make_pair(2, 2)}},
    {make_pair(3, 3), {make_pair(2, 3)}},
    {make_pair(4, 0), {make_pair(3, 0), make_pair(4, 1)}},
    {make_pair(4, 1), {make_pair(4, 0), make_pair(4, 2)}},
    {make_pair(4, 2), {make_pair(4, 1), make_pair(4, 3)}},
    {make_pair(4, 3), {make_pair(4, 2)}}
};
    // Create a TupleMap to represent the graph
    cellMap graph2 = {
        {make_pair(0,0),{make_pair(0,1),make_pair(1,0)}},
        {make_pair(0,1),{make_pair(0,0),make_pair(1,1),make_pair(0,2)}},
        {make_pair(0,2),{make_pair(0,1),make_pair(1,2)}},
        {make_pair(1,0),{make_pair(0,0),make_pair(1,1)}},
        {make_pair(1,1),{make_pair(1,0),make_pair(0,1),make_pair(1,2)}},
        {make_pair(1,2),{make_pair(0,2),make_pair(1,1)}}
    };

    // Create an instance of the Graphe class
    Graphe g(0, 0);

    // Use the construire method to build the graph
    g.construire(graph);

    // Retrieve the built graph using getGraph method
    cellMap retrievedGraph = g.getGraph();

    // Print the retrieved graph
    for (const auto& pair : retrievedGraph) {
        const auto& cell = pair.first;
        const auto& cellSet = pair.second;

        cout << "(" << get<0>(cell) << ", " << get<1>(cell) << "): ";
        for (const auto& value : cellSet) {
            cout << "(" << get<0>(value) << ", " << get<1>(value) << ") ";
        }
        cout << endl;
    }

    cellSet voisinsSet = g.getVoisins(make_pair(1, 1));
    cout << "Voisins of (1, 1): ";
    for (const auto& v : voisinsSet) {
        cout << "(" << get<0>(v) << ", " << get<1>(v) << ") ";
    }
    cout << endl;

    Aretes aretesVec = g.aretes();
    cout << "Aretes: ";
    for (const auto& a : aretesVec) {
        const auto& u = a.first;
        const auto& v = a.second;
        cout << "(" << u.first << ", " << u.second << ") - (" << v.first << ", " << v.second << ") ///";
    }
    cout << endl;

    bool isArete = g.arete(make_pair(0, 0), make_pair(1, 2));
    cout << "Is (0, 0) - (1, 2) an edge? " << (isArete ? "Yes" : "No") << endl;
    cellSet vus;
    cellSet parcoursProfSet = g.parcours_prof(make_pair(0, 0),vus);
    cout << "Parcours prof starting from (0, 0): ";
    for (const auto& v : parcoursProfSet) {
        
        cout << "(" << v.first<< ", " << v.second << ") ";
    }
    cout << endl;
    cellSet val1;
    cell val2;
    cellSet parcoursChSet = g.parcours_ch(make_pair(0, 0),val2,val1);
    cout << "Parcours ch starting from (0, 0): ";
    for (const auto& v : parcoursChSet) {
        cout << "(" << v.first << ", " << v.second << ") ";
    }
    cout << endl;

    cellSet cheminsSet = g.chemins(make_pair(0, 0), make_pair(2, 2));
    cout << "Chemins from (0, 0) to (2, 2): ";
    for (const auto& v : cheminsSet) {
        cout << "(" << v.first << ", " << v.second << ") ";
    }
    Labyrinthe lab(4,5,graph);
    
    
    cout << endl;
    return 0;
}
