#include "graph.hpp"
//
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

    cellSet voisinsSet = g.voisins(make_pair(1, 1));
    cout << "Voisins of (1, 1): ";
    for (const auto& v : voisinsSet) {
        cout << "(" << get<0>(v) << ", " << get<1>(v) << ") ";
    }
    cout << endl;

    vector<Arete> aretesVec = g.aretes();
    cout << "Aretes: ";
    for (const auto& a : aretesVec) {
        const auto& u = a.first;
        const auto& v = a.second;
        cout << "(" << get<0>(u) << ", " << get<1>(u) << ") - (" << get<0>(v) << ", " << get<1>(v) << ") ///";
    }
    cout << endl;

    bool isArete = g.arete(make_pair(0, 0), make_pair(1, 2));
    cout << "Is (0, 0) - (1, 2) an edge? " << (isArete ? "Yes" : "No") << endl;

    cellSet parcoursProfSet = g.parcours_prof(make_pair(0, 0));
    cout << "Parcours prof starting from (0, 0): ";
    for (const auto& v : parcoursProfSet) {
        cout << "(" << get<0>(v) << ", " << get<1>(v) << ") ";
    }
    cout << endl;

    cellSet parcoursChSet = g.parcours_ch(make_pair(0, 0));
    cout << "Parcours ch starting from (0, 0): ";
    for (const auto& v : parcoursChSet) {
        cout << "(" << get<0>(v) << ", " << get<1>(v) << ") ";
    }
    cout << endl;

    cellSet cheminsSet = g.chemins(make_pair(0, 0), make_pair(2, 2));
    cout << "Chemins from (0, 0) to (2, 2): ";
    for (const auto& v : cheminsSet) {
        cout << "(" << get<0>(v) << ", " << get<1>(v) << ") ";
    }
    cout << endl;
    return 0;
}
