#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

Sommet::Sommet(std::string id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}

void Sommet::ajouterVoisin(const Sommet* voisin){
    m_voisins.push_back(voisin);
}

void Sommet::afficherData() const
{
    std::cout << "Id : " << m_id << std::endl
              << "x: " << m_x << std::endl
              << "y: " << m_y << std::endl;

    std::cout << "Voisins : " << std::endl;
    for (auto elem : m_voisins)
    {
        std::cout << elem->getId() << " ";
    }

    std::cout << std::endl;
}

std::string Sommet::getId() const
{
    return m_id;
}

Sommet::~Sommet()
{
    //dtor
}
