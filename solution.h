#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "graphe.h"
#include "arete.h"
#include "svgfile.h"

class Solutions : public Graphe
{
public:
    Solutions(float cout1, float cout2, std::vector<Arete*> aretes,std::vector<Sommet*> sommets);
    Solutions(std::vector<Arete*> aretes, std::vector<Sommet*> sommets);
    Solutions();
    ~Solutions() {};
    void SVGpoint(Svgfile &svgout,std::string color,int echelle, int cpt);
    float getCout1();
    float getCout2();
    void afficher();

protected:
    float m_coutT1;
    float m_coutT2;

private:
};
void toutDessiner(std::vector<Solutions> tabSolus,Svgfile &svgout,int echelle);
void dessinerPareto( std::unordered_map<float,Solutions> CombinaisonsForte,std::unordered_map<float,Solutions> CombinaisonsFaible,Svgfile &svgout, int echelle);
std::unordered_map<float,Solutions> pareto(std::vector<Solutions> tabSolus,Svgfile &svgout,int echelle);

#endif // SOLUTION_H_INCLUDED
