#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arete.h"

class Graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        Graphe(std::string, std::string);

        void afficher() const;
        void kruskal();
       std::unordered_map<Sommet*,Sommet*>  dijkstra();
       void afficherDijkstra();

        int getOrdre() const
        {
          return (int)m_sommets.size();
        }

        std::vector<Sommet*> getvectsommet()
        {
            return m_sommets;
        }


        ~Graphe();

    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;

        //std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)

};

#endif // GRAPHE_H
