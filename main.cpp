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



    g.afficherPrim(g.prim());
    g.afficherPrim(g.prim("0", 1));

    return 0;
}
