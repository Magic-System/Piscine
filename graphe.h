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
        ///constructeur qui charge le graphe en m�moire
        //format du fichier ordre/liste des sommets/taille/liste des ar�tes
        Graphe(std::string, std::string);

        void afficher() const;
        void dessinerGraphSVG(Svgfile &svgout) const;
        void dessinerGraph() const;

        int getOrdre() const
        {
          return (int)m_sommets.size();
        }
        //void prim(std::string id = "0", int indicePoids = 0) const;
        std::vector<Arete*> prim(std::string id = "0", int indicePoids = 0) const;
        void afficherPrim(const std::vector<Arete*>) const;

        ~Graphe();

    protected:

    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;

        //std::unordered_map<std::string,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)

};

void SVGgraph(Svgfile &svgout, float cout1, float cout2);

#endif // GRAPHE_H
