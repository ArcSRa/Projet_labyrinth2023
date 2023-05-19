#include "graph.hpp"

//coins = [" ", "╶", "╵", "└", "╴", "─", "┘", "┴", "╷", "┌", "│", "├", "┐", "┬", "┤", "┼"]
using namespace std;

class Labyrinth : private Graphe{
    private:
    
    public :
    unordered_map<pair<int,int>,unordered_set<int>> dic_adjac(int w, int h) {

    }
    
    vector<pair<int,int>> murs_cellule(int cell)
        vector<pair<int,int>> coins=Graphe.aretes();
        for (const pair& coin : coins) {
            if (coin.first != cell || coin.second != cell) {
                coins.erase(coin);
            }
        }
    unordered_set<int> voisins_cellule(int cell)
        
    void ouvrir_passage(x, y)
        Graphe.ajouter_arete









};