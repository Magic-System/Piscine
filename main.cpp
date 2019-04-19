#include <iostream>
#include "graphe.h"
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"
#include "solution.h"
#include <math.h>

///Temps bruteforce par graphe :
///Broadway : 0.1 sec
///Cubetown : 0.2 sec
///Triville : 1 sec
///Manhanttan : 1 min

int main()
{
    Svgfile svgout("output.svg");
    ///Broadway
    Graphe g{"files/broadway.txt", "files/broadway_weights_0.txt"};
    ///Cubetown
    //Graphe g{"files/cubetown.txt", "files/cubetown_weights_0.txt"};
    ///Triville
    //Graphe g{"files/triville.txt", "files/triville_weights_0.txt"};
    ///Manhattan
    //Graphe g{"files/manhattan.txt", "files/manhattan_weights_0.txt"};

    g.afficher();

    //g.afficherPrim(g.prim());
    //g.afficherPrim(g.prim("0", 1));
    SVGrepere(svgout);
    std::vector<std::vector<bool>> test = g.sol_admissible(svgout);
    std::vector<Solutions> tabSolus = g.calculCout(test);


   // toutDessiner(tabSolus,svgout);

    g.afficherDijkstra();

    pareto(tabSolus,svgout);

    std::cout << test.size() << "   solutions" << std::endl;
    return 0;
}
