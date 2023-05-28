#include "Labyrinthe.hpp"
//
int main() {


    Labyrinthe lab(5, 4);
    lab.reset();
    cout << lab;
    //lab.ouvrir_passage(make_pair(1,3),make_pair(2,3)) ;

    cellMap map = lab.dic_adjac(5, 4);
    for (const auto& pair : map) {
        const auto& cell = pair.first;
        const auto& cellSet = pair.second;

        cout << "(" << get<0>(cell) << ", " << get<1>(cell) << "): ";
        for (const auto& value : cellSet) {
            cout << "(" << get<0>(value) << ", " << get<1>(value) << ") ";
        }
        cout << endl;
    }
    lab.ouvrir_passage(make_pair(1,1),make_pair(3,4));
    return 0;
}