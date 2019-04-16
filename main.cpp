#include <iostream>
#include "graphe.h"
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"



int main()
{
    Svgfile svgout("output.svg");
    Graphe g{"manhattan.txt", "manhattan_weights_0.txt"};
    g.afficher();
    g.dessinerGraphSVG(svgout);
    g.dessinerGraph();
    g.kruskal(svgout);



    return 0;
}
