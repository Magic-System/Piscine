#include <iostream>
#include "graphe.h"
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"





int main()
{
    Svgfile svgout("output.svg");
    //Graphe g{"files/broadway_2.txt", "files/broadway_2_weights_0.txt"};
    //Graphe g{"files/cubetown.txt", "files/cubetown_weights_0.txt"};
    Graphe g{"files/triville.txt", "files/triville_weights_0.txt"};
    //Graphe g{"files/manhattan.txt", "files/manhattan_weights_0.txt"};

    g.afficher();
    g.dessinerGraphSVG(svgout);
    g.dessinerGraph();



    g.afficherDijkstra();

    return 0;
}
