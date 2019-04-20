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
    for(unsigned int i=0;i<tabSolus.size();++i)
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
    for(int i=0; i<tabSolus.size(); ++i)
    {
        CombinaisonsForte[id] = tabSolus[i];
        id++;
    }

    for(auto it1 = CombinaisonsForte.begin(); it1!= CombinaisonsForte.end(); it1++)
    {
       for(auto it2 = CombinaisonsForte.begin(); it2!= CombinaisonsForte.end();)
       {
           if((((it1->second.getCout1()) <= (it2->second.getCout1()))&&((it1->second.getCout2()) < (it2->second.getCout2())))||(((it1->second.getCout1()) < (it2->second.getCout1()))&&(((it1->second.getCout2()) <= (it2->second.getCout2()))))||(((it1->second.getCout1()) == (it2->second.getCout1()))&&((it1->second.getCout2()) == (it2->second.getCout2())))&&((((it1->first) != (it2->first)))))
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
 std::map<Sommet*,float> Solutions::dijkstra(Sommet *initial,int indicepoids)
{
    std::unordered_map<Sommet*,Sommet*> l_pred;
    std::multimap<float, Sommet*> decouvert;
    std::map<Sommet*,float> marque;

    float distancetotal = 0;

    marque.insert({initial,distancetotal});

    while(marque.size() != m_sommets.size())
    {
        for(voisin : initial->getvoisins())
        {
            if(!marque.count(voisin))
         {
            std::multimap<float,Sommet*> ::iterator it;
            std::multimap<float,Sommet*> ::iterator suppr;

          float distance =0;

          for(a:m_aretes)
          {
            if((a->getSommet(0) == initial && a->getSommet(1) == voisin) || a->getSommet(1) == initial && a->getSommet(0) == voisin)
            distance = distancetotal + a->getPoids()[indicepoids];
          }
                bool valider = true;
                bool supprimer = false;

                for(it = decouvert.begin(); it!= decouvert.end(); ++it)
                {
                    if(voisin == (*it).second)
                    {
                       if(distance >= (*it).first)
                        valider = false;
                       else
                       {
                         suppr = it;
                         supprimer = true;
                       }
                    }
                }
                if(valider == true)
                {
                    if(supprimer == true)
                    {
                        decouvert.erase(suppr);
                        l_pred.erase(l_pred.find(voisin));
                    }

                    decouvert.insert({distance,voisin});
                    l_pred.insert({voisin,initial});
                }

                distance = distancetotal;
            }
        }

        marque.insert({(*decouvert.begin()).second,(*decouvert.begin()).first});
        distancetotal = (*decouvert.begin()).first;

        for(sommet_suivant:m_sommets)
        {
            if(sommet_suivant == (*decouvert.begin()).second)
            initial = sommet_suivant;

        }
        decouvert.erase(decouvert.begin());
      }

      return marque;
}

  std::vector<std::pair<double,double>> bi_objectif(std::vector<Solutions> tabSolus,Svgfile &svgout)
{
    std::vector<std::pair<double,double>> coordonnees;
    std::map<Sommet *,float> sommet_dijkstra;

    for(s: tabSolus)
    {
          float x =0,y =0;

          x = s.getCout1();

          for(sommet :s.getm_sommets())
          {
              sommet_dijkstra = s.dijkstra(sommet,1);

              for(dij : sommet_dijkstra)
              {
                  y+= dij.second;
              }
          }

          std::cout<<x<<" ";
          std::cout<<y<<" ";
          coordonnees.push_back({x,y});
    }

    return coordonnees;
}




