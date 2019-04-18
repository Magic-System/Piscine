#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"

class Solutions
{
    public:
        Solutions(float cout1, float cout2):m_coutT1{cout1}, m_coutT2{cout2}
        {} ;
        Solutions() {};
        ~Solutions(){};
        void SVGpoint(Svgfile &svgout);
        float getCout1();
        float getCout2();
        void afficher();

    protected:

    private:
       float m_coutT1;
       float m_coutT2;



};
void toutDessiner(std::vector<Solutions> tabSolus,Svgfile &svgout);
void pareto(std::vector<Solutions> tabSolus);
#endif // SOLUTION_H_INCLUDED
