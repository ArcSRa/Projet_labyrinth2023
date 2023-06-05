#include "Labyrinthe.hpp"
//
int main() {
/*    Graphe g;

    // Construct the graph
    unordered_map<int, unordered_set<int>> A{
        {4, {}},
        {1, {2, 3}},
        {3, {1}},
        {2, {3, 4}}
        
    };
    g.construire(A);

    // Add vertices and edges
    g.ajouter_sommet(5);
    g.ajouter_arete(4, 5);

    // Get neighbors of a vertex
    unordered_set<int> neighbors = g.voisins(2);
    cout << "Neighbors of vertex 2: ";
    for (int neighbor : neighbors) {
        cout << neighbor << " ";
    }
    cout << endl;

    // Get all edges
    vector<pair<int, int>> edges = g.aretes();
    cout << "Edges: ";
    for (const auto& edge : edges) {
        cout << "(" << edge.first << ", " << edge.second << ") ";
    }
    cout << endl;

    // Check if an edge exists
    bool hasEdge = g.arete(3, 1);
    cout << "Edge (3, 1) exists? " << (hasEdge ? "Yes" : "No") << endl;

    // Find a path between two vertices
    vector<int> path = g.chemins(1, 4);
    cout << "Path from vertex 1 to vertex 4: ";
    for (int vertex : path) {
        cout << vertex << " ";
    }
    cout << endl;

    // Check if a path exists between two vertices
    bool hasPath = g.existe_chemin(2, 4);
    cout << "Path from vertex 2 to vertex 4 exists? " << (hasPath ? "Yes" : "No") << endl;

    // Perform a breadth-first search
    unordered_map<int, int> distances = g.parcours_larg(1);
    cout << "Distances from vertex 1: " << endl;
    for (const auto& pair : distances) {
        cout << "Vertex: " << pair.first << ", Distance: " << pair.second << endl;
    }
*/

    /*Graphe g(5, 5, false); // Create a graph with width = 5, height = 5, and undirected edges

    // Adding vertices
    g.ajouter_sommet(make_tuple(0, 0));
    g.ajouter_sommet(make_tuple(0, 1));
    g.ajouter_sommet(make_tuple(1, 0));
    g.ajouter_sommet(make_tuple(1, 1));
    g.ajouter_sommet(make_tuple(2, 2));

    // Adding edges
    g.ajouter_arete(make_tuple(0, 0), make_tuple(0, 1));
    g.ajouter_arete(make_tuple(0, 1), make_tuple(1, 1));
    g.ajouter_arete(make_tuple(1, 0), make_tuple(1, 1));
    g.ajouter_arete(make_tuple(0, 0), make_tuple(1, 0));
    g.ajouter_arete(make_tuple(1, 1), make_tuple(2, 2));

    // Get all vertices
    TupleMap graph = g.getGraph();
    cout << "Vertices:" << endl;
    for (const auto& vertex : graph) {
        Tuple v = vertex.first;
        cout << "(" << get<0>(v) << ", " << get<1>(v) << ")" << endl;
    }

    // Get all edges
    vector<Arete> edges = g.aretes();
    cout << "Edges:" << endl;
    for (const auto& edge : edges) {
        Tuple u = edge.first;
        Tuple v = edge.second;
        cout << "(" << get<0>(u) << ", " << get<1>(u) << ") -> (" << get<0>(v) << ", " << get<1>(v) << ")" << endl;
    }*/

    /*cellMap graph = {
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
    cout << endl;*/

    Labyrinthe lab(4, 5);
    cellMap mapLab = lab.getGraph();
    cout << "mapLab :" << endl;
    for (const auto& vertex : mapLab) {
        cell v = vertex.first;
        cout << "(" << get<0>(v) << ", " << get<1>(v) << ")" << endl;
    }
    cout << lab;

    /*Graphe g(5,4);
    cell c=make_pair(0,0);
    g.ajouter_sommet(c);
    for (const auto& vertex : g.getGraph()) {
        cell v = vertex.first;
        cout << "(" << get<0>(v) << ", " << get<1>(v) << ")" << endl;
    }*/

    /*cellMap map = lab.dic_adjac(5, 4);
    for (const auto& pair : map) {
        const auto& cell = pair.first;
        const auto& cellSet = pair.second;

        cout << "(" << get<0>(cell) << ", " << get<1>(cell) << "): ";
        for (const auto& value : cellSet) {
            cout << "(" << get<0>(value) << ", " << get<1>(value) << ") ";
        }
        cout << endl;
    }*/

    /*Aretes murs = lab.murs_cellule(make_pair(1,1));
    for (const auto& arete : murs) {
        cout << "First cell: (" << arete.first.first << ", " << arete.first.second << ")" << endl;
        cout << "Second cell: (" << arete.second.first << ", " << arete.second.second << ")" << endl;
        cout << "-----------------------" << endl;
    }*/
    return 0;
}
