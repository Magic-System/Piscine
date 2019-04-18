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
        Graphe(std::vector<Sommet*> sommets, std::vector<Arete*> aretes);
        void afficher() const;
        void dessinerGraphSVG(Svgfile &svgout) const;
        void dessinerGraph() const;
        int getOrdre() const
        {
          return (int)m_sommets.size();
        }
        std::vector<Arete*> getArete() const
        {
            return m_aretes;
        }
        //void prim(std::string id = "0", int indicePoids = 0) const;
        Graphe prim(std::string id = "0", int indicePoids = 0) const;
        void afficherPrim(const Graphe,Svgfile &svgout) const;
        int Connexe() const;

        ~Graphe();

    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
        float m_cout1;
        float m_cout2;

//       std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)

};

void SVGrepere(Svgfile &svgout);
void SVGpoint(Svgfile &svgout, float cout1, float cout2);

#endif // GRAPHE_H
