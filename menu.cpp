#include <iostream>
#include "graphe.h"
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"
#include "solution.h"
#include <math.h>
#include "windows.h"


void menuprincipal()
{
    int choix = 0;
    Svgfile svgout("output.svg");
    std::string nom_fichier,nom_fichier_poids;

    std::cout<<std::string(5,' ')<<"MENU PRINCIPAL"<<std::endl<<std::endl;

    std::cout<<std::string(5,' ')<<"1.BROADWAY"<<std::endl
             <<std::string(5,' ')<<"2.CUBETOWN"<<std::endl
             <<std::string(5,' ')<<"3.TRIVILLE"<<std::endl
             <<std::string(5,' ')<<"4.MANHATTAN"<<std::endl;

     do{std::cin >> choix;}while(choix<1 || choix>4);

     switch(choix)
     {
         case 1:  nom_fichier = "files/broadway.txt";
                  nom_fichier_poids = "files/broadway_weights_0.txt";
                  break;
         case 2:  nom_fichier = "files/cubetown.txt";
                  nom_fichier_poids = "files/cubetown_weights_0.txt";
                  break;
         case 3:  nom_fichier = "files/triville.txt";
                  nom_fichier_poids = "files/triville_weights_0.txt";
                  break;
         case 4:  nom_fichier = "files/manhattan.txt";
                  nom_fichier_poids = "files/manhattan_weights_0.txt";
                  break;

     }

     Graphe g(nom_fichier,nom_fichier_poids);
     system("CLS");

    std::cout<<std::string(5,' ')<<"MENU PRINCIPAL"<<std::endl<<std::endl;
    std::cout<<std::string(5,' ')<<"1.Entrees/sorties, representations, arbres couvrants mono-objectif "<<std::endl
             <<std::string(5,' ')<<"2.Double ponderation, optimisation arbre couvrant bi-objectif "<<std::endl
             <<std::string(5,' ')<<"3.Optimisation bi-objectif cout / distances "<<std::endl;

     choix = 0;
       do{std::cin >> choix;}while(choix<1 || choix>3);

       std::vector<Solutions> tabSolus;
       std::vector<std::vector<bool>> test;

     switch(choix)
     {
         case 1:   g.afficher();
                   g.dessinerGraph();
                   g.afficherPrim(g.prim());
                   g.afficherPrim(g.prim("0", 1));
                   break;
         case 2:    SVGrepere(svgout);
                   test = g.sol_admissible(svgout);
                   tabSolus = g.calculCout(test);
                    break;
         case 3: //bi_objectif(tabSolus,svgout);
                break;

     }


}
