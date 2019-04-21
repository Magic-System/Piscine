#include "arete.h"
#include <iostream>
#include <vector>

Arete::Arete(std::string id, Sommet* s1, Sommet* s2, std::vector<float> poids) : m_id{id}, m_sommet1{s1}, m_sommet2{s2}
{
    for (auto elem : poids)
        m_poids.push_back(elem);
}

void Arete::dessinerArete(Svgfile &svgout,int posy)  const
{
    int x1 = m_sommet1->getx();
    int y1 = m_sommet1->gety();
    int x2 = m_sommet2->getx();
    int y2 = m_sommet2->gety();
    //Ligne arete
    svgout.addLine(x1, y1+posy, x2, y2+posy, 2, "green");
    //Texte poids arete
    svgout.addText((x1+x2)/2,(y1+y2)/2,m_poids[0], "green");
    svgout.addText((x1+x2)/2+7,(y1+y2)/2,";", "green");
    svgout.addText((x1+x2)/2+10,(y1+y2)/2,m_poids[1], "green");
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


Arete::~Arete()
{

}
