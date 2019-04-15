#include <iostream>
#include "graphe.h"
#include "sommet.h"
#include "arete.h"

int main()
{
    Graphe g{"broadway.txt", "broadway_weights_0.txt"};
    g.afficher();

    return 0;
}
