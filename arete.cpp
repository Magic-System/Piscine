#include "arete.h"
#include <iostream>

Arete::Arete(std::string id, Sommet* s1, Sommet* s2, std::vector<float> poids) : m_id{id}, m_sommet1{s1}, m_sommet2{s2}
{
    for (auto elem : poids)
        m_poids.push_back(elem);
}

std::string Arete::getId()  const
{
    return m_id;
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
