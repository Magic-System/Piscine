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
    std::cout << "affichage du graph" << std::endl;
    calculCout(g.getArete());
  //  g.parcoursBFS();
    //g.Connexe();
     g.afficher();
    g.dessinerGraphSVG(svgout);
    g.dessinerGraph();
    SVGrepere(svgout);



    std::cout << "Debut de Prime" << std::endl;
    g.afficherPrim(g.prim(),svgout);
    //g.prim().dessinerGraphSVG(svgout);
    std::cout << "suite de Prime" << std::endl;
    g.afficherPrim(g.prim("0", 1),svgout);

    return 0;
}
