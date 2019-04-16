#include <fstream>
#include <iostream>
#include "graphe.h"
#include <algorithm>


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

void Graphe::dessinerGraphSVG(Svgfile &svgout) const
{
    double x1;
    double y1;
    double x2;
    double y2;
       for(const auto val2: m_aretes)
       {
           x1=val2->getSommet1()->getx();
           y1=val2->getSommet1()->gety();
           x2=val2->getSommet2()->getx();
           y2=val2->getSommet2()->gety();
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
           ofs << "LR_" << val2->getSommet1()->getId() <<" -> "<< "LR_" << val2->getSommet2()->getId()<<"[label =\"" <<val2->getPoids()[0]<<"/"<<val2->getPoids()[1]<<"\""<< "];" << std::endl;
       }
       ofs << "}" << std::endl;
       ofs.close();
   }

}

void Graphe::kruskal(Svgfile &svgout)
{
    std::vector<Arete*> Mes_aretes;
    std::vector<Sommet*> Mes_sommets;
    std::vector<Arete*> Mes_aretes_selectionnes;

    float poidstotal1 = 0;
    float poidstotal2 = 0;

    for( a: m_aretes)
    {
        Mes_aretes.push_back(a);
    }
    for( s: m_sommets)
    {
        Mes_sommets.push_back(s);
    }

    std::sort(Mes_aretes.begin(), Mes_aretes.end(), [](Arete* a1, Arete * a2)
    {
        return a1->getPoids()[1] < a2->getPoids()[1];
    });

    for(a : Mes_aretes)
    {
        std::string id1,id2;

        for(s : Mes_sommets)
        {
            if( a->getSommet1()->getx() == s->getx() && a->getSommet1()->gety() == s->gety())
                id1 = s->getId();
            if( a->getSommet2()->getx() == s->getx() && a->getSommet2()->gety() == s->gety())
                id2 = s->getId();
        }

        if( id1 != id2)
        {
            for(s_connexe:Mes_sommets)
            {
                if(s_connexe->getId() == id2)
                s_connexe->setId(id1);
            }

            Mes_aretes_selectionnes.push_back(a);
            poidstotal1 += a->getPoids()[0];
            poidstotal2 += a->getPoids()[1];

        }
    }
  std::cout<<"solution : ("<<poidstotal1<<";"<<poidstotal2<<")";
  SVGgraph(svgout, poidstotal1, poidstotal2);
}

Graphe::~Graphe()
{
    //dtor
}
