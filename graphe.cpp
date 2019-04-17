#include <fstream>
#include <iostream>
#include <bitset>
#include <math.h>
#include "graphe.h"

Graphe::Graphe(std::string nomFichier, std::string fichierPoids){
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

    std::string id_poids;
    int nb_poids;
    int t_poids;
    f_poids >> t_poids;
    f_poids >> nb_poids;

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

std::vector<std::vector<bool>> Graphe::sol_admissible()
{
    unsigned int m = m_aretes.size();
    //Solutions filtré une premiere fois pour garder seulement les solutions utilisant n-1 aretes avec n egal l'ordre du graphe (nb de sommets)
    std::vector<std::vector<bool>> solutions_temp;
    //Solutions filtré pour ne garder que les solutions qui ne créee pas de cycle
    std::vector<std::vector<bool>> solutions;


    for (unsigned int i=0; i < pow(2, m); ++i)
    {
        unsigned int iTemp = i, k = 0;
        std::vector<bool> temp;
        for (unsigned int j = m; j>0; --j)
        {
            if (k <= m_sommets.size()-1)
            {
                if (iTemp-pow(2, j-1) >= 0)
                {
                    temp.push_back(1);
                    iTemp = iTemp-pow(2, j-1);
                    k++;
                }
                else
                    temp.push_back(0);
            }
        }
        if (k == m_sommets.size()-1)
        {
            solutions_temp.push_back(temp);
            //for (auto elem : temp)
                //std::cout << elem;
            //std::cout << std::endl;
        }
    }
    std::cout << "done  " << solutions_temp.size() << std::endl;

    //On ne garde que les solutions ne creant pas de cycle en verifiant si les aretes selectionnée sont connectés a tout les sommets du graphe
    for (auto vectBool : solutions_temp)
    {
        std::unordered_set<Sommet*> cc;
        int i=0;
        for (auto elem : vectBool)
        {
            if (elem == 1)
            {
                for (auto a : m_aretes)
                {
                    if (a->getId() == std::to_string(i))
                    {
                        cc.insert(a->getSommet(0));
                        cc.insert(a->getSommet(1));
                    }
                }
            }
            i++;
        }
        if (cc.size() == m_sommets.size())
            solutions.push_back(vectBool);
    }

    //On retourne les solutions filtre
    return solutions;
}

std::vector<Arete*> Graphe::prim(std::string id, int indicePoids) const
{
    std::vector<Sommet*> decouverts;
    std::vector<Arete*> areteParcouru;

    //On ajoute le sommet de depart dans la liste des sommets decouverts
    for(auto elem : m_sommets)
        if (elem->getId() == id)
            decouverts.push_back(elem);

    do{
        //liste d'arete potentiellement choisie
        std::vector<Arete*> a;

        //On parcours nos sommets decouverts
        for (auto s : decouverts)
            //On parcours la liste des arretes du graphe
            for (auto sArete : m_aretes)
                //Si le sommet de depart de l'arete est identique a un sommet decouverts et que le sommet d'arrivé n'est pas decouvert alors on ajoute cette arete a notre liste d'arete potentiellement choisi
                if (sArete->getSommet(0) == s)
                {
                    int i=0;
                    for (auto elem : decouverts)
                        if (sArete->getSommet(1) == elem)
                            i++;
                    if (i == 0)
                        a.push_back(sArete);
                }


        Arete* areteSelec;
        //Valeur tres grande pour comparer les poids des arete potentiellement choisi
        float poidPrec = 1000000000;
        //On compare le poids d'indice recu en parametre avec le poid precedent afin de trouver l'arete ayant le plus petit poid
        for (auto arete : a)
        {
            std::vector<float> poids = arete->getPoids();
            if (poids[indicePoids] <= poidPrec)
            {
                poidPrec = poids[indicePoids];
                areteSelec = arete;
            }
        }
        //L'arete ayant le plus petit poid est ajouté a la liste des aretes parcouru par prim
        //Le sommet d'arrivé de cette arete est ajouté a la liste des sommets decouverts
        decouverts.push_back(areteSelec->getSommet(1));
        areteParcouru.push_back(areteSelec);

    //tant que l'ordre de la liste des sommets decouverts n'est pas le meme que l'ordre du graphe
    }while(decouverts.size() != m_sommets.size());

    return areteParcouru;
}

void Graphe::afficherPrim(std::vector<Arete*> a)
{
    //On initialise le vector a 0
    std::vector<float> poidsTot(a[0]->getPoids().size(), 0.0);

    //std::cout << "Prim a partir du Sommet : " << id << ", en fonction du poids d'indice : " << indicePoids << std::endl;

    for (auto elem : a)
    {
        //On affiche les arete parcouru par prim
        elem->afficherArete();
        //On calcule les poids totaux
        std::vector<float> p = elem->getPoids();
        for (unsigned int i=0; i<p.size(); ++i)
        {
            poidsTot[i] = poidsTot[i] + p[i];
        }
    }
    //On affiche les poids totaux
    std::cout << "\n(";
    for (auto elem : poidsTot)
        std::cout << elem << ";";
    std::cout << ")" << std::endl;
}

Graphe::~Graphe()
{
    //dtor
}
