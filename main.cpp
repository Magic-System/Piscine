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
    std::vector<std::vector<bool>> Partie2 = g.sol_admissible(0);
    std::vector<Solutions> tabSolusP2 = g.calculCout(Partie2);

    std::vector<std::vector<bool>> Partie3 = g.sol_admissible(1);
    std::vector<Graphe> tabGrapheP3 = g.transformation(Partie3);


    std::vector<Solutions> tabSolusP3=CalculDijkstra(tabGrapheP3);
    for(int i =0;i < tabSolusP3.size();++i)
    {
        tabSolusP3[i].afficher();
    }
     pareto(tabSolusP3,svgout);

   /* for(int i =0; i<tabGrapheP3.size();++i)
    {
    std::cout<< tabGrapheP3[i].getArete().size() << std::endl;
    } */


    //std::vector<std::pair<float,float>>temp = bi_objectif(tabSolus,svgout) ;
    //paretoDijkstra(Partie3 , svgout);


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
    std::cout <<"Partie 2 : " << Partie2.size() << "   solutions" << std::endl;
    std::cout <<"Partie 3 : " << Partie3.size() << "   solutions" << std::endl;
    return 0;
}
