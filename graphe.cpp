#include <fstream>
#include <iostream>
#include "graphe.h"

Graphe::Graphe(std::string nomFichier, std::string fichierPoids){
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.push_back(new Sommet{id,x,y});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_s1;
    std::string id_s2;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extrémités
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture id arete");
        ifs>>id_s1; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_s2; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");

        Sommet* s1;
        Sommet* s2;

        for (auto elem : m_sommets)
        {
            if (elem->getId() == id_s1)
                s1 = elem;
            if (elem->getId() == id_s2)
                s2 = elem;
        }
        s1->ajouterVoisin(s2);
        m_aretes.push_back(new Arete(id, s1, s2));
    }

    ifs.close();
    std::ifstream f_poids{fichierPoids};
    if (!f_poids)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichierPoids );

    int nb_poids;
    f_poids >> taille;
    f_poids >> nb_poids;

    for (int i=0; i<taille; ++i)
    {
        float p;
        std::vector<float> poids;
        Arete* a;
        f_poids >> id;
        for (auto elem : m_aretes)
        {
            if (id == elem->getId())
                a = elem;
        }

        for (int i=0; i<nb_poids; ++i)
        {
            f_poids >> p;
            poids.push_back(p);
        }
        a->initPoids(poids);

    }

}

void Graphe::afficher() const
{
    std::cout<<"Graphe : "<<m_sommets.size()<<std::endl;
    for (const auto s : m_sommets)
    {
        std::cout<<"  sommet :";
        s->afficherData();
        //s->afficherVoisins();
        std::cout << std::endl;
    }
    for (const auto a : m_aretes)
    {
        std::cout<<"  arete :";
        a->afficherArete();
        std::cout << std::endl;
    }
}

Graphe::~Graphe()
{
    //dtor
}
