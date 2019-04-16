#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arete.h"
#include "svgfile.h"


class Graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        Graphe(std::string, std::string);

        void afficher() const;
        void dessinerGraphSVG(Svgfile &svgout) const;
        void dessinerGraph() const;
        void kruskal(Svgfile &svgout);

        int getOrdre() const
        {
          return (int)m_sommets.size();
        }

        ~Graphe();

    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;

        //std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)

};

void SVGgraph(Svgfile &svgout, float cout1, float cout2);

#endif // GRAPHE_H
