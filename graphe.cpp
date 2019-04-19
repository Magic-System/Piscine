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

        Sommet* s1 = nullptr;
        Sommet* s2 = nullptr;

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

std::vector<std::vector<bool>> Graphe::sol_admissible(Svgfile &svgout)
{
    unsigned int m = m_aretes.size();
    //Solutions filtré une premiere fois pour garder seulement les solutions utilisant n-1 aretes avec n egal l'ordre du graphe (nb de sommets)
    //std::vector<std::vector<bool>> solutions_temp;
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
            if (rech_connexe(temp) == true)
                solutions.push_back(temp);
        }
    }
    //On retourne les solutions filtre
    return solutions;
}

//void Graphe::frontierePareto(std::vector<std::vector<bool>>)    const

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

bool Graphe::rech_connexe(std::vector<bool> combinaison)    const
{
    std::vector<int> tabConnex;
    bool connex = false;

    //On rempli le tableau de connexite avec des valeurs differentes pour chaque sommet
    for (unsigned int i =0; i< m_sommets.size(); ++i)
        tabConnex.push_back(i);

    //On parcours notre combinaire binaire
    for (unsigned int i=0;i<combinaison.size(); ++i)
    {
        //Si le bit est a 1
        if (combinaison[i] == 1)
        {
            //On recupere l'indice de l'arete correspondant a ce bit
            int iArete = abs(i-(m_aretes.size()-1));
            //On recupere les id des sommets aux extremites de l'arete
            int id1 = std::stoi(m_aretes[iArete]->getSommet(0)->getId());
            int id2 = std::stoi(m_aretes[iArete]->getSommet(1)->getId());

            //On verifie notre tableau de connexité pour savoir si les deux sommets font partie de la meme composante connexe
            //Si il ne sont pas deja ensemble, on les met ensemble
            if (tabConnex[id1] != tabConnex[id2])
            {
                int temp1 =tabConnex[id1];
                int temp2 = tabConnex[id2];
                for(size_t j=0; j<tabConnex.size();++j)
                {
                    if(tabConnex[j] == temp1) tabConnex[j]=temp2;
                }
            }
        }
    }
    unsigned int i=0;
    //On compte le nombre de sommet ayant la meme composante connexe
    for (auto elem : tabConnex)
        if (elem == tabConnex[0])
            i++;

    //Si tous les sommets sont dans la meme connexe on return true, sinon false
    if (i == tabConnex.size())
        connex = true;
    else
        connex = false;

    return connex;
}

/* bool Graphe::rech_connexe(std::vector<bool> combinaison)    const
{
    std::unordered_map<std::string,int> tabConnex;
    bool connex = false;
    int c=0;

    //On rempli le tableau de connexite avec des valeurs differentes pour chaque sommet
    for (int i =0; i< m_sommets.size(); ++i)
        {tabConnex.insert({m_sommets[c]->getId(),i});
         ++c;}
    //On parcours notre combinaire binaire
    for (unsigned int i=0;i<combinaison.size(); ++i)
    {
        //Si le bit est a 1
        if (combinaison[i] == 1)
        {
            //On recupere l'indice de l'arete correspondant a ce bit
            int iArete = abs(i-(m_aretes.size()-1));
            //On recupere les id des sommets aux extremites de l'arete
            std::string id1=m_aretes[iArete]->getSommet(0)->getId();
            std::string id2=m_aretes[iArete]->getSommet(1)->getId();

        //    int id1 = std::stoi(m_aretes[iArete]->getSommet(0)->getId());
        //   int id2 = std::stoi(m_aretes[iArete]->getSommet(1)->getId());

            //On verifie notre tableau de connexité pour savoir si les deux sommets font partie de la meme composante connexe
            //Si il ne sont pas deja ensemble, on les met ensemble
            if (tabConnex[id1] != tabConnex[id2])
            {
              tabConnex[id1] = (int)m_sommets.size();
              tabConnex[id2] = (int)m_sommets.size();
              for(int i=0;i<tabConnex.size();++i)
              {

                 if (tabConnex[id1] != tabConnex[id2])
                 {
                    tabConnex[id1] = (int)m_aretes.size();
                    tabConnex[id2] = (int)m_aretes.size();
                 }

              }
            }
        }
    }
    int compteur=0;
   // int test = tabConnex.begin()->second;
   //On compte le nombre de sommet ayant la meme composante connexe
     for(auto it = tabConnex.begin(); it!= tabConnex.end(); it++)
    {
              if (it->second == tabConnex.begin()->second) compteur++;
    }

    //Si tous les sommets sont dans la meme connexe on return true, sinon false
    if (compteur == tabConnex.size())
        connex = true;
    else
        connex = false;

    return connex;
}
*/
void Graphe::dessinerGraph() const
{
   std::ofstream ofs{"GrapheOut.txt"};
   if(!ofs)
   std::cerr <<"error !"<<std::endl;
   else
   {
      ofs << "digraph{" << std::endl << "size= \"50,50 \"" << "node [shape = circle];" <<std::endl;
       for (auto val : m_sommets)
       {
           ofs << "LR_" << val->getId() <<"[pos=\"" << val->getx()/10 << "," << abs(val->gety() /10 -100) << "!" << "\"];" << std::endl;
       }
       for(auto val2 : m_aretes)
       {
           ofs << "LR_" << val2->getSommet(0)->getId() <<" -> "<< "LR_" << val2->getSommet(1)->getId()<<"[label =\"" <<val2->getPoids()[0]<<"/"<<val2->getPoids()[1]<<"\""<< "];" << std::endl;
       }
       ofs << "}" << std::endl;
       ofs.close();
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
     /*      if((x1>x2)&&(y1>y2)) { svgout.addLine(x2+10,y2+10,x2+12.5,y2+17.5,"red");
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
                                  svgout.addLine(x2-15,y2,x2-20,y2-5,"red"); }  */
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

void Graphe::afficherPrim(const Graphe a,Svgfile &svgout)  const
{
    //On initialise le vector a 0
    std::vector<float> poidsTot(a.getArete()[0]->getPoids().size(), 0.0);

    //std::cout << "Prim a partir du Sommet : " << id << ", en fonction du poids d'indice : " << indicePoids << std::endl;

    for (const auto elem : a.m_aretes)
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

 std::vector<Arete*> Graphe::getArete() const
{
return m_aretes;
}

Graphe::~Graphe()
{
    //dtor
}

void SVGrepere(Svgfile &svgout)
{
    svgout.addLine(600,50,600,250, "black");
    svgout.addLine(600,250,800,250, "black");
    svgout.addLine(600,50,595,55, "black");
    svgout.addLine(600,50,605,55, "black");
    svgout.addLine(800,250,795,245, "black");
    svgout.addLine(800,250,795,255, "black");
    svgout.addText(560,40,"cout 1", "black");
    svgout.addText(810,250,"cout 2", "black");
}


std::vector<Solutions> Graphe::calculCout(std::vector<std::vector<bool>> solutions)
 {
    std::vector<Solutions> tabSolus;
    float coutT1=0;
    float coutT2=0;
    for(unsigned int i=0;i<solutions.size(); ++i)
    {
        coutT1=0;
        coutT2=0;

        for(unsigned int j=0;j<solutions[i].size(); ++j)
        {
            if (solutions[i][j] == 1)
           {
            //On recupere l'indice de l'arete correspondant a ce bit
            int iArete = abs(j-(m_aretes.size()-1));
            coutT1= coutT1+ m_aretes[iArete]->getPoids()[0];
            coutT2= coutT2+ m_aretes[iArete]->getPoids()[1];
           }
        }
        Solutions x(coutT1, coutT2);
        tabSolus.push_back(x);
    }
   // std::cout << "cout 1 :"  << coutT1 << "cout 2 :"  << coutT2 <<std::endl;

    return tabSolus;
 }
