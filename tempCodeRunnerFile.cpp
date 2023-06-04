Labyrinthe lab(5, 4);
    //lab.reset();
    cellMap mapLab = lab.getGraph();
    cout << "mapLab :" << endl;
    for (const auto& vertex : mapLab) {
        cell v = vertex.first;
        cout << "(" << get<0>(v) << ", " << get<1>(v) << ")" << endl;
    }
    cout << lab;