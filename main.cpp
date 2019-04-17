#include <iostream>
#include "graphe.h"
#include "sommet.h"
#include "arete.h"

int main()
{
    Graphe g{"manhattan.txt", "manhattan_weights_0.txt"};
    g.afficher();

    g.dijkstra();
    g.afficherDijkstra();

    return 0;
}
