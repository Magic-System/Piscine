#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Sommet
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        Sommet(std::string,double,double);
        void ajouterVoisin(Sommet*);

        void afficherData() const;
        std::string getId() const;

        void setId(std::string id)
        {
            m_id = id;
        }

        double getx() const
        {
          return m_x;
        }
         double gety() const
        {
          return m_y;
        }

        std::vector<Sommet*> getvoisins()
        {
            return m_voisins;
        }



        ~Sommet();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<Sommet*> m_voisins;

        /// Donn�es sp�cifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
