#include "arete.h"
#include <iostream>

Arete::Arete(std::string id, Sommet* s1, Sommet* s2) : m_id{id}, m_sommet1{s1}, m_sommet2{s2}
{
}

std::string Arete::getId()  const
{
    return m_id;
}

Sommet* Arete::getSommet1()  const
{
    return m_sommet1;
}
Sommet* Arete::getSommet2()  const
{
    return m_sommet2;
}

std::vector<float> Arete::getPoids()  const
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

void Arete::initPoids(std::vector<float> poids)
{
    for (auto elem : poids)
        m_poids.push_back(elem);
}

Arete::~Arete()
{

}
