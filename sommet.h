#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "svgfile.h"


class Sommet
{
public:
    ///constructeur qui re�oit en params les donn�es du sommet
    Sommet(std::string,double,double);

    void ajouterVoisin(Sommet*);
    void afficherData() const;
    std::string getId() const;
    double getx() const;
    double gety() const;
    std::vector< Sommet*> getvoisins() const;

    void dessinerSommet(Svgfile &svgout,int posy)   const;

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
