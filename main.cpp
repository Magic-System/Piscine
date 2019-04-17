#include <iostream>
#include "graphe.h"
#include "sommet.h"
#include "arete.h"

#include <math.h>



int main()
{
    //Graphe g{"files/broadway_2.txt", "files/broadway_2_weights_0.txt"};
    //Graphe g{"files/cubetown.txt", "files/cubetown_weights_0.txt"};
    Graphe g{"files/triville.txt", "files/triville_weights_0.txt"};
    //Graphe g{"files/manhattan.txt", "files/manhattan_weights_0.txt"};
    g.afficher();

    //g.afficherPrim(g.prim());
    //g.afficherPrim(g.prim("0", 1));

    std::vector<std::vector<bool>> test = g.sol_admissible();

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
