#include "solution.h"


void Solutions::SVGpoint(Svgfile &svgout)
{
   svgout.addDisk(m_coutT1+600,250-m_coutT2,1,"green");
}

void toutDessiner(std::vector<Solutions> tabSolus,Svgfile &svgout)
{
    for(unsigned int i=0;i<tabSolus.size();++i)
    {
        tabSolus[i].SVGpoint(svgout);
    }
}

float Solutions::getCout1()
{
    return m_coutT1;
}

float Solutions::getCout2()
{
    return m_coutT2;
}

void Solutions::afficher()
{
    std::cout << "cout 1 : " << m_coutT1 << "  cout 2 : " << m_coutT2 << std::endl;
}

void pareto(std::vector<Solutions> tabSolus)
{
    /*std::unordered_map<int,Solutions> CombinaisonsForte;
    std::unordered_map<int,Solutions> CombinaisonsFaible;
    for(unsigned int i=0; i<tabSolus.size();++i)
    {
        CombinaisonsForte[i] = tabSolus[i];
    }
    for(auto it1 = CombinaisonsForte.begin(); it1!= CombinaisonsForte.end(); it1++)
    {
       for(auto it2 = CombinaisonsForte.begin(); it2!= CombinaisonsForte.end(); it2++)
       {
           if((it1->second.getCout1() >= it2->second.getCout1())&&(it1->second.getCout2() >= it2->second.getCout2()))
           {
               it2.erase();
           }
       }
    }
    */

}
