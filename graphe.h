#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arete.h"

class Graphe
{
    public:
        ///constructeur qui charge le graphe en m�moire
        //format du fichier ordre/liste des sommets/taille/liste des ar�tes
        Graphe(std::string, std::string);

        void afficher() const;
        void kruskal();
       std::unordered_map<std::string,std::string>  dijkstra();
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
        /// Le r�seau est constitu� d'une collection de sommets
        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;

        //std::unordered_map<std::string,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)

};

#endif // GRAPHE_H
