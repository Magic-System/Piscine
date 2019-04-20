#include "solution.h"

Solutions::Solutions( float cout1, float cout2,std::vector<Arete*> aretes,std::vector<Sommet*> sommets) : Graphe{aretes,sommets}, m_coutT1{cout1}, m_coutT2{cout2}
{}

Solutions::Solutions(std::vector<Arete*> aretes, std::vector<Sommet*> sommets) : Graphe{aretes, sommets}
{}

Solutions::Solutions()
{}

void Solutions::SVGpoint(Svgfile &svgout,std::string color)
{
    svgout.addDisk(m_coutT1+600,250-m_coutT2,0.4,color);
}

void toutDessiner(std::vector<Solutions> tabSolus,Svgfile &svgout)
{
    for(unsigned int i=0; i<tabSolus.size(); ++i)
    {
        tabSolus[i].SVGpoint(svgout,"green");
    }
}

void dessinerPareto( std::unordered_map<float,Solutions> CombinaisonsForte,std::unordered_map<float,Solutions> CombinaisonsFaible,Svgfile &svgout)
{
    for(auto it1 = CombinaisonsForte.begin(); it1!= CombinaisonsForte.end(); it1++)
    {
        std::cout <<"Voici les aretes presentes dans combinaisonsForte "<< std::endl << "cout 1 :" << it1->second.getCout1() << "cout 2 :" << it1->second.getCout2() << std::endl;
        it1->second.SVGpoint(svgout,"green");
    }
    for(auto it2 = CombinaisonsFaible.begin(); it2!= CombinaisonsFaible.end(); it2++)
    {
        it2->second.SVGpoint(svgout,"red");
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

std::unordered_map<float,Solutions> pareto(std::vector<Solutions> tabSolus,Svgfile &svgout)
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
                //std::cout<< "v1 : "<< it2->first << std::endl;
                CombinaisonsFaible.insert({it2->first, it2->second});
                //std::cout<< "v1 : "<< it2->first << std::endl;
                it2= CombinaisonsForte.erase(it2);
                // std::cout<< "v1 : "<< it2->first << std::endl;
            }
            else ++it2;
        }
    }

    dessinerPareto(CombinaisonsForte,CombinaisonsFaible,svgout);

    return CombinaisonsForte;

}

void paretoDijkstra(std::vector<std::pair<float,float>>tabSolus,Svgfile &svgout)
{
    std::unordered_map<int,std::pair<float,float>> CombinaisonsForte;
    std::unordered_map<int,std::pair<float,float>> CombinaisonsFaible;
    int id=0;
    for(unsigned int i=0; i<tabSolus.size(); ++i)
    {
        CombinaisonsForte[id] = tabSolus[i];
        id++;
    }
    int compteur=0;
    for(auto it1 = CombinaisonsForte.begin(); it1!= CombinaisonsForte.end(); it1++)
    {
        for(auto it2 = CombinaisonsForte.begin(); it2!= CombinaisonsForte.end();)
        {
            if(((( it1->second.first <= it2->second.first) && (it1->second.second < it2->second.second))
               || ((it1->second.first < it2->second.first) && ((it1->second.second <= it2->second.second))))
               || (((it1->second.first == it2->second.first) && (it1->second.second == it2->second.second)) && (((it1->first != it2->first)))))
            {
                // std::cout<< "v1 : "<< it2->first << std::endl;
                CombinaisonsFaible.insert({it2->first, it2->second});
                // std::cout<< "v1 : "<< it2->first << std::endl;
                it2= CombinaisonsForte.erase(it2);
                // std::cout<< "v1 : "<< it2->first << std::endl;
            }
            else ++it2;
        }
    }
    dessinerParetoDijkstra(CombinaisonsForte,CombinaisonsFaible, svgout);
}

void dessinerParetoDijkstra(std::unordered_map<int,std::pair<float,float>> CombinaisonsForte, std::unordered_map<int,std::pair<float,float>> CombinaisonsFaible, Svgfile &svgout)
{
    for(auto it2 = CombinaisonsFaible.begin(); it2!= CombinaisonsFaible.end(); it2++)
    {
        svgout.addDisk(5*it2->second.first+50,550-(5*it2->second.second),2,"red");
    }
    for(auto it1 = CombinaisonsForte.begin(); it1!= CombinaisonsForte.end(); it1++)
    {
        svgout.addDisk(5*it1->second.first+50,550-(5*it1->second.second),2,"green");
    }
}




