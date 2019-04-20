#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet(std::string,double,double);
        void ajouterVoisin(Sommet*);

        void afficherData() const;
        std::string getId() const;
        double getx() const;
        double gety() const;

         std::vector< Sommet*> getvoisins()
        {
            return m_voisins;
        }




        ~Sommet();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<Sommet*> m_voisins;

        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
