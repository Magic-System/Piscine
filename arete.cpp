#include "arete.h"
#include <iostream>
#include <fstream>
#include <vector>

Arete::Arete(std::string id, Sommet* s1, Sommet* s2, std::vector<float> poids) : m_id{id}, m_sommet1{s1}, m_sommet2{s2}
{
    for (auto elem : poids)
        m_poids.push_back(elem);
}

std::string Arete::getId()  const
{
    return m_id;
}

Sommet* Arete::getSommet(bool i) const
{
    if (i == 0)
        return m_sommet1;
    else
        return m_sommet2;
}

std::vector<float> Arete::getPoids()    const
{
    return m_poids;
}

void Arete::afficherArete() const
{
    std::cout << m_id << "   " << m_sommet1->getId() << " -> " << m_sommet2->getId() << std::endl;
    std::cout << "  Poids : ";
    for (auto elem : m_poids)
    {
        std::cout << elem << "   ";
    }
    std::cout << std::endl;

}

void Arete::dessinerGraph() const
{
   std::ofstream ofs{"GrapheOut.txt"};
   if(!ofs)
   std::cerr <<"error !"<<std::endl;
   else
   {
      ofs << "digraph finite_state_machine{" << std::endl << "rankdir=LR;" <<std::endl << "size= \"300,300 \"" << "node [shape = cirlce];" <<std::endl;

           ofs << "LR_" << m_sommet1->getId() <<"[pos=\"" << m_sommet1->getx()/10 << "," << m_sommet1->gety() /10 << "!" << "\"];" << std::endl;


           ofs << "LR_" << m_sommet2->getId() <<"[pos=\"" << m_sommet2->getx()/10 << "," << m_sommet2->gety() /10 << "!" << "\"];" << std::endl;

      /* for(auto val2 : m_sommet1 )
       {
           ofs << "LR_" << val2->getSommet(0)->getId() <<" -> "<< "LR_" << val2->getId()<<"[label =\"" <<val2->getPoids()[0]<<"/"<<val2->getPoids()[1]<<"\""<< "];" << std::endl;
       } */
       ofs << "}" << std::endl;
       ofs.close();
   }

}



Arete::~Arete()
{

}
 std::pair<float,float> calculCout(std::vector<Arete*> mesAretes)
 {
     std::pair<float,float> coutTotaux;
     float coutT1=0;
     float coutT2=0;
     for(int i=0; i < mesAretes.size();i++)
     {
         coutT1= coutT1+mesAretes[i]->getPoids()[0];
         coutT2= coutT2+mesAretes[i]->getPoids()[1];
     }
     std::cout << "cout 1 :"  << coutT1 << "cout 2 :"  << coutT2 <<std::endl;
    coutTotaux.first= coutT1;
    coutTotaux.second= coutT2;
     return coutTotaux;

}
