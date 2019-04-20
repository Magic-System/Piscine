#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"

class Solutions;

class Graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        Graphe(std::string, std::string);
        Graphe(std::vector<Arete*> aretes, std::vector<Sommet*> sommets);
        Graphe(){};
        void afficher() const;
        std::vector<std::vector<bool>> sol_admissible(Svgfile &svgout);
        //void frontierePareto(std::vector<std::vector<bool>>)    const;
        //void prim(std::string id = "0", int indicePoids = 0) const;
        std::vector<Arete*> prim(std::string id = "0", int indicePoids = 0) const;
        void afficherPrim(std::vector<Arete*>);
        void afficherPrim(const Graphe,Svgfile &svgout) const;
        bool rech_connexe(std::vector<bool>) const;
        std::string parcoursBFS()   const;
        void dessinerGraph() const;
        void dessinerGraphSVG(Svgfile &svgout) const;
        std::vector<Arete*> getArete() const;
        std::vector<Solutions> calculCout(std::vector<std::vector<bool>> solutions);
        void afficherDijkstra();
        std::vector<Sommet*> getm_sommets()const;



        ~Graphe();

    protected:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;


    private:

        //std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)

};

void SVGrepere(Svgfile &svgout);


#endif // GRAPHE_H
