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
    int echelle =0 ;
    std::string nom_fichier,nom_fichier_poids;

    std::cout<<std::string(6,' ')<<"MENU PRINCIPAL"<<std::endl<<std::endl;

    std::cout<<std::string(5,' ')<<"1.BROADWAY"<<std::endl
             <<std::string(5,' ')<<"2.CUBETOWN"<<std::endl
             <<std::string(5,' ')<<"3.TRIVILLE"<<std::endl
             <<std::string(5,' ')<<"4.MANHATTAN"<<std::endl;

     do{std::cin >> choix;}while(choix<1 || choix>4);

     switch(choix)
     {
         case 1:  nom_fichier = "files/broadway.txt";
                  nom_fichier_poids = "files/broadway_weights_0.txt";
                  echelle =1;
                  break;
         case 2:  nom_fichier = "files/cubetown.txt";
                  nom_fichier_poids = "files/cubetown_weights_0.txt";
                  echelle =2;
                  break;
         case 3:  nom_fichier = "files/triville.txt";
                  nom_fichier_poids = "files/triville_weights_0.txt";
                  echelle =3;
                  break;
         case 4:  nom_fichier = "files/manhattan.txt";
                  nom_fichier_poids = "files/manhattan_weights_0.txt";
                  echelle =4;
                  break;

     }

     Graphe g(nom_fichier,nom_fichier_poids);
     system("CLS");

    std::cout<<std::string(6,' ')<<"MENU PRINCIPAL"<<std::endl<<std::endl;
    std::cout<<std::string(5,' ')<<"1.Entrees/sorties, representations, arbres couvrants mono-objectif "<<std::endl
             <<std::string(5,' ')<<"2.Double ponderation, optimisation arbre couvrant bi-objectif "<<std::endl
             <<std::string(5,' ')<<"3.Optimisation bi-objectif cout / distances "<<std::endl;

     choix = 0;
       do{std::cin >> choix;}while(choix<1 || choix>3);

       std::vector<std::vector<bool>> sol;
       std::vector<Solutions> tabSolus;
       std::vector<Graphe> tabGrapheP3;
       Svgfile svgout("output.svg");
       Graphe Prim1(g.prim(),g.getm_sommets());
       Graphe Prim2(g.prim("0", 1),g.getm_sommets());


     switch(choix)
     {
         case 1:   g.afficher();
                   g.dessinerGraph();
                   g.afficherPrim(g.prim());
                   g.afficherPrim(g.prim("0", 1));
                   svgout.addText(10,100,"Vanilla :","black");
                   g.dessinerGraphSVG(svgout,10 , 0);
                   svgout.addText(440,100,"Prim 1 :","black");
                   Prim1.dessinerGraphSVG(svgout,450 , 0);
                   svgout.addText(280,430,"Prim 2 :","black");
                   Prim2.dessinerGraphSVG(svgout,300 , 350);
                   break;

         case 2:   SVGrepere(svgout);
                   sol = g.sol_admissible(0);
                   tabSolus = g.calculCout(sol);
                   echelle = 0;
                   pareto(tabSolus,svgout, echelle);
                    break;

         case 3:  SVGrepere(svgout);
                  sol = g.sol_admissible(1);
                  tabGrapheP3 = g.transformation(sol);
                  tabSolus=CalculDijkstra(tabGrapheP3);
                  pareto(tabSolus,svgout,echelle);
                  break;

     }


}
