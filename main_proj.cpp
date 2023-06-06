#include "Labyrinthe.hpp"
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
    Labyrinthe lab(10, 11);
    lab.reset();
    cout << lab;
    //lab.ouvrir_passage(make_pair(1,3),make_pair(2,3)) ;

    // cellMap map = lab.dic_adjac(5, 4);
    // for (const auto& pair : map) {
    //     const auto& cell = pair.first;
    //     const auto& cellSet = pair.second;

    //     cout << "(" << get<0>(cell) << ", " << get<1>(cell) << "): ";
    //     for (const auto& value : cellSet) {
    //         cout << "(" << get<0>(value) << ", " << get<1>(value) << ") ";
    //     }
    //     cout << endl;
    // }
   // lab.ouvrir_passage(make_pair(1,1),make_pair(3,4));
    //lab.construire_aldous_broder();
    lab.construire_fusion();
    cout<<lab;
    return 0;
}