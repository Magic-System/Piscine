#include <fstream>
#include <iostream>
#include "graphe.h"
#include <algorithm>
#include <map>
#include "math.h"

Graphe::Graphe(std::string nomFichier, std::string fichierPoids)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    std::ifstream f_poids{fichierPoids};
    if (!f_poids)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichierPoids );

    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.push_back(new Sommet{id,x,y});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_s1;
    std::string id_s2;

    std::string id_poids;
    int nb_poids;
    int t_poids;
    f_poids >> t_poids;
    f_poids >> nb_poids;

    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extrémités
        ifs>>id;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture id arete");
        ifs>>id_s1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_s2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture arete sommet 2");

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
        std::vector<float> poids;

        float p;
        f_poids >> id_poids;

        for (int i=0; i<nb_poids; ++i)
        {
            f_poids >> p;
            poids.push_back(p);
        }

        m_aretes.push_back(new Arete(id, s1, s2, poids));
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

void Graphe::kruskal()
{
    std::vector<Arete*> Mes_aretes_selectionnes;

    float poidstotal1 = 0;
    float poidstotal2 = 0;

    std::sort(m_aretes.begin(), m_aretes.end(), [](Arete *a1, Arete  *a2)
    {
        return a1->getpoids()[1] < a2->getpoids()[1];
    });


    for(a : m_aretes)
    {
        std::string id1,id2;

        for(s : m_sommets)
        {
            if( a->getsommet1()->getx() == s->getx() && a->getsommet1()->gety() == s->gety())
                id1 = s->getId();
            if( a->getsommet2()->getx() == s->getx() && a->getsommet2()->gety() == s->gety())
                id2 = s->getId();
        }

        if( id1 != id2)
        {
            for(s_connexe:m_sommets)
            {
                if(s_connexe->getId() == id2)
                    s_connexe->setId(id1);

            }


            Mes_aretes_selectionnes.push_back(a);
            poidstotal1 += a->getpoids()[0];
            poidstotal2 += a->getpoids()[1];

        }
    }

    for(a:Mes_aretes_selectionnes)
    {
        a->afficherArete();
    }

    std::cout<<"solution : ("<<poidstotal1<<";"<<poidstotal2<<")";
}

std::unordered_map<std::string,std::string> Graphe::dijkstra()
{
    std::unordered_map<std::string,std::string> l_pred;
    std::multimap<float,std::string> decouvert;
    std::multimap<float,std::string> marque;

    float distancetotal = 0;

    Sommet* s = m_sommets.front();
    marque.insert({distancetotal,s->getId()});

    while(marque.size() != m_sommets.size())
    {
        for(voisin : s->getvoisins())
        {
            bool continuer = true;

        std::multimap<float,std::string>::iterator it;

        for(it = marque.begin();it != marque.end();++it)
            {
                if(voisin->getId() == (*it).second)
                    continuer = false;
            }

            if(continuer == true)
            {
                float d1=0,d2=0,distance =0;

                d1 = (voisin->getx() - s->getx()) * (voisin->getx() - s->getx());
                d2 = (voisin->gety() - s->gety()) * (voisin->gety() - s->gety());

                distance = distancetotal + sqrt( d1 + d2);

                std::multimap<float,std::string> ::iterator it;
                bool valider = true;

                for(it = decouvert.begin(); it!= decouvert.end(); ++it)
                {
                    if(voisin->getId() == (*it).second)
                    {
                        if(distance >= (*it).first)
                        {
                            valider = false;
                        }

                        else
                        {
                            decouvert.erase(it);

                            std::unordered_map<std::string,std::string> ::iterator ite;

                            for(ite = l_pred.begin(); ite!= l_pred.end(); ++ite)
                            {
                                if((*ite).second == voisin->getId())
                                    l_pred.erase(ite);
                            }
                        }
                    }
                }

                if(valider == true)
                {

                    decouvert.insert({distance,voisin->getId()});
                    l_pred.insert({voisin->getId(),s->getId()});
                }
                distance = distancetotal;
            }
        }

        marque.insert({(*decouvert.begin()).first,(*decouvert.begin()).second});

        distancetotal = (*decouvert.begin()).first;

        for(sommet_suivant:m_sommets)
        {
            if(sommet_suivant->getId() == (*decouvert.begin()).second)
                s = sommet_suivant;
        }

        decouvert.erase(decouvert.begin());
      }

      return l_pred;
}

void Graphe::afficherDijkstra()
{
    std::unordered_map<std::string,std::string> l_pred;

     l_pred = dijkstra();

        for(auto s:l_pred)
    {
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;

        while(pred.second!= m_sommets.front()->getId())
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<m_sommets.front()->getId()<<std::endl;
    }

}

Graphe::~Graphe()
{
    //dtor
}
