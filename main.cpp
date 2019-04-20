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
///Manhanttan : 58 sec

int main()
{
    Svgfile svgout("output.svg");
    Graphe g{"files/broadway.txt", "files/broadway_weights_0.txt"};
    //Graphe g{"files/cubetown.txt", "files/cubetown_weights_0.txt"};
    //Graphe g{"files/triville.txt", "files/triville_weights_0.txt"};
    //Graphe g{"files/manhattan.txt", "files/manhattan_weights_0.txt"};
    g.afficher();

    //g.afficherPrim(g.prim());
    //g.afficherPrim(g.prim("0", 1));
    SVGrepere(svgout);
    std::vector<std::vector<bool>> test = g.sol_admissible(svgout);
    std::vector<Solutions> tabSolus = g.calculCout(test);

    bi_objectif(tabSolus,svgout);


   /* for(int i = 0; i< tabSolus.size();++i)
    {
        tabSolus[i].afficher();
    } */
    //toutDessiner(tabSolus,svgout);

/*
    for (auto elem : test)
    {
        for (auto b : elem)
            std::cout << b;
        std::cout << std::endl;
    }
*/
    std::cout << test.size() << "   solutions" << std::endl;
    return 0;
}
