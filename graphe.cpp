#include <fstream>
#include <iostream>
#include <bitset>
#include <math.h>
#include "graphe.h"
#include <algorithm>
#include <map>


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

void Graphe::dessinerGraphSVG(Svgfile &svgout) const
{
    double x1;
    double y1;
    double x2;
    double y2;
       for(const auto val2: m_aretes)
       {
           x1=val2->getSommet(0)->getx();
           y1=val2->getSommet(0)->gety();
           x2=val2->getSommet(1)->getx();
           y2=val2->getSommet(1)->gety();
           svgout.addLine(x1, y1, x2, y2, "red");
           if((x1>x2)&&(y1>y2)) { svgout.addLine(x2+10,y2+10,x2+12.5,y2+17.5,"red");
                                  svgout.addLine(x2+10,y2+10,x2+17.5,y2+12.5,"red"); }
           if((x1==x2)&&(y1>y2)) { svgout.addLine(x2,y2+15,x2-5,y2+20,"red");
                                  svgout.addLine(x2,y2+15,x2+5,y2+20,"red"); }
           if((x1<x2)&&(y1>y2)) { svgout.addLine(x2-10,y2+10,x2-17.5,y2+12.5,"red");
                                  svgout.addLine(x2-10,y2+10,x2-12.5,y2+17.5,"red"); }
           if((x1>x2)&&(y1==y2)) { svgout.addLine(x2+15,y2,x2+20,y2-5,"red");
                                  svgout.addLine(x2+15,y2,x2+20,y2+5,"red"); }
           if((x1>x2)&&(y1<y2))  { svgout.addLine(x2+10,y2-10,x2+12.5,y2-17.5,"red");
                                  svgout.addLine(x2+10,y2-10,x2+17.5,y2-12.5,"red"); }
           if((x1==x2)&&(y1<y2)) { svgout.addLine(x2,y2-15,x2-5,y2-20,"red");
                                  svgout.addLine(x2,y2-15,x2+5,y2-20,"red"); }
           if((x1<x2)&&(y1<y2)) { svgout.addLine(x2-15,y2-15,x2-17.5,y2-22.5,"red");
                                  svgout.addLine(x2-15,y2-15,x2-22.5,y2-17.5,"red"); }
           if((x1<x2)&&(y1==y2)) { svgout.addLine(x2-15,y2,x2-20,y2+5,"red");
                                  svgout.addLine(x2-15,y2,x2-20,y2-5,"red"); }
           svgout.addText((x1+x2)/2,(y1+y2)/2 ,val2->getPoids()[0], "green");
           svgout.addText((x1+x2)/2+7,(y1+y2)/2 ,";", "green");
           svgout.addText((x1+x2)/2+10,(y1+y2)/2 ,val2->getPoids()[1], "green");



       }
       for(const auto val: m_sommets)
       {
             svgout.addDisk(val->getx(),val->gety(),15,"white");
             svgout.addCircle(val->getx(), val->gety(), 15,2, "black");
             svgout.addText(val->getx()-2.5, val->gety()+2.5, val->getId(), "purple");
       }
}

void SVGgraph(Svgfile &svgout, float cout1, float cout2)
{
    svgout.addLine(600,50,600,250, "black");
    svgout.addLine(600,250,800,250, "black");
    svgout.addLine(600,50,595,55, "black");
    svgout.addLine(600,50,605,55, "black");
    svgout.addLine(800,250,795,245, "black");
    svgout.addLine(800,250,795,255, "black");
    svgout.addDisk(cout1+600,250-cout2,3,"green");
    svgout.addText(560,40,"cout 1", "black");
    svgout.addText(810,250,"cout 2", "black");


}

void Graphe::dessinerGraph() const
{
   std::ofstream ofs{"GrapheOut.txt"};
   if(!ofs)
   std::cerr <<"error !"<<std::endl;
   else
   {
      ofs << "digraph finite_state_machine{" << std::endl << "rankdir=LR;" <<std::endl << "size= \"300,300 \"" << "node [shape = cirlce];" <<std::endl;
       for (auto val : m_sommets)
       {
           ofs << "LR_" << val->getId() <<"[pos=\"" << val->getx()/10 << "," << val->gety() /10 << "!" << "\"];" << std::endl;
       }
       for(auto val2 : m_aretes)
       {
           ofs << "LR_" << val2->getSommet(0)->getId() <<" -> "<< "LR_" << val2->getSommet(1)->getId()<<"[label =\"" <<val2->getPoids()[0]<<"/"<<val2->getPoids()[1]<<"\""<< "];" << std::endl;
       }
       ofs << "}" << std::endl;
       ofs.close();
   }

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

void Graphe::afficherPrim(const std::vector<Arete*> a)  const
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
 std::unordered_map<Sommet*,Sommet*> Graphe::dijkstra(Sommet *initial,int indicepoids)
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
            if(a->getsommet1() == initial && a->getsommet2() == voisin)
            distance = distancetotal + a->getPoids()[indicepoids];
          }
                bool valider = true;
                bool supprimer = false;

                for(it = decouvert.begin(); it!= decouvert.end(); ++it)
                {
                    if(voisin == (*it).second)
                    {
                       if(distance > (*it).first)
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
                        decouvert.erase(distance);
                        l_pred.erase(l_pred.find(voisin));
                    }

                    decouvert.insert({distance,voisin});
                    l_pred.insert({voisin,initial});
                }

                distance = distancetotal;
            }
        }

        marque.insert({(*decouvert.begin()).second,(*decouvert.begin()).first});
        distancetotal = (*marque.begin()).second;

        for(sommet_suivant:m_sommets)
        {
            if(sommet_suivant == (*decouvert.begin()).second)
            initial = sommet_suivant;

        }
        decouvert.erase(decouvert.begin());
      }

      return l_pred;
}

void Graphe::afficherDijkstra()
{
    std::unordered_map<Sommet*, Sommet *> l_pred;

    for(initial : m_sommets)
    {
      l_pred = dijkstra(initial,0);

        for(auto s:l_pred)
    {
        std::cout<<s.first->getId()<<" <--- ";
        std::pair<Sommet*,Sommet*> pred=s;

        while(pred.second!= initial)
        {
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first->getId()<<" <--- ";
        }
        std::cout<<initial->getId()<<std::endl;

    }
    }
}

Graphe::~Graphe()
{
    //dtor
}
