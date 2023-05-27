#include "graph.hpp"

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

    Graphe g(5, 5, false); // Create a graph with width = 5, height = 5, and undirected edges

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
    }
    return 0;
}
