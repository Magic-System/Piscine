#include "solution.h"

Solutions::Solutions( float cout1, float cout2,std::vector<Arete*> aretes,std::vector<Sommet*> sommets) : Graphe{aretes,sommets}, m_coutT1{cout1}, m_coutT2{cout2}
{}

Solutions::Solutions(std::vector<Arete*> aretes, std::vector<Sommet*> sommets) : Graphe{aretes, sommets}
{}

Solutions::Solutions()
{}

void Solutions::SVGpoint(Svgfile &svgout,std::string color,int echelle)
{
    switch(echelle)
    {
     case 0 : if (color == "red")svgout.addDisk(5*m_coutT1+50,350-m_coutT2*5,1,color);
              if (color == "green")svgout.addDisk(5*m_coutT1+50,350-m_coutT2*5,2.5,color);
              break;
     case 1 :  if (color == "red")svgout.addDisk(6.5*m_coutT1+50,350-m_coutT2,1,color);
              if (color == "green")svgout.addDisk(6.5*m_coutT1+50,350-m_coutT2,2.5,color);
              break;
     case 2 : if (color == "red")svgout.addDisk(4*m_coutT1+50,350-m_coutT2/4,1,color);
              if (color == "green")svgout.addDisk(4*m_coutT1+50,350-m_coutT2/4,2.5,color);
              break;
     case 3 : if (color == "red")svgout.addDisk(3*m_coutT1+50,350-m_coutT2/8,1,color);
              if (color == "green")svgout.addDisk(3*m_coutT1+50,350-m_coutT2/8,2.5,color);
              break;
     case 4 : if (color == "red")svgout.addDisk(2*m_coutT1+50,350-m_coutT2/24,1,color);
              if (color == "green")svgout.addDisk(2*m_coutT1+50,350-m_coutT2/24,2.5,color);
              break;
    }
}

void toutDessiner(std::vector<Solutions> tabSolus,Svgfile &svgout ,int echelle)
{
    for(unsigned int i=0; i<tabSolus.size(); ++i)
    {
        tabSolus[i].SVGpoint(svgout,"green", echelle);
    }
}

void dessinerPareto( std::unordered_map<float,Solutions> CombinaisonsForte,std::unordered_map<float,Solutions> CombinaisonsFaible,Svgfile &svgout,int echelle)
{
    for(auto it2 = CombinaisonsFaible.begin(); it2!= CombinaisonsFaible.end(); it2++)
    {
        it2->second.SVGpoint(svgout,"red", echelle);
    }
    std::cout <<"Voici les aretes presentes dans combinaisonsForte "<< std::endl;
    int compteur =1;
    for(auto it1 = CombinaisonsForte.begin(); it1!= CombinaisonsForte.end(); it1++)
    {
        std::cout<<"Combinaison n" <<compteur<<" ----> "<< " cout 1: " << it1->second.getCout1() << " et cout 2: " << it1->second.getCout2() << std::endl;
        it1->second.SVGpoint(svgout,"green", echelle);
        compteur++;
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

std::unordered_map<float,Solutions> pareto(std::vector<Solutions> tabSolus,Svgfile &svgout, int echelle)
{
    std::unordered_map<float,Solutions> CombinaisonsForte;
    std::unordered_map<float,Solutions> CombinaisonsFaible;
    float id=0;
    for(unsigned int i=0; i<tabSolus.size(); ++i)
    {
        CombinaisonsForte[id] = tabSolus[i];
        id++;
    }

    for(auto it1 = CombinaisonsForte.begin(); it1!= CombinaisonsForte.end(); it1++)
    {
        for(auto it2 = CombinaisonsForte.begin(); it2!= CombinaisonsForte.end();)
        {
            if((((it1->second.getCout1()) <= (it2->second.getCout1())) && ((it1->second.getCout2()) < (it2->second.getCout2())))
               || (((it1->second.getCout1()) < (it2->second.getCout1())) && (((it1->second.getCout2()) <= (it2->second.getCout2()))))
               || ((((it1->second.getCout1()) == (it2->second.getCout1()))&&((it1->second.getCout2()) == (it2->second.getCout2()))) && ((((it1->first) != (it2->first))))))
            {
                CombinaisonsFaible.insert({it2->first, it2->second});
                it2= CombinaisonsForte.erase(it2);
            }
            else ++it2;
        }
    }

    dessinerPareto(CombinaisonsForte,CombinaisonsFaible,svgout,echelle);

    return CombinaisonsForte;

}








