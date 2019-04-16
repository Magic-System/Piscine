#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include "sommet.h"

class Arete
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        Arete(std::string, Sommet*, Sommet*);

        void afficherArete()    const;
        std::string getId() const;
        Sommet* getSommet1() const;
        Sommet* getSommet2() const;
        std::vector<float> getPoids() const;
        void initPoids(std::vector<float>);

        ~Arete();

    protected:

    private:
        std::string m_id;
        std::vector<float> m_poids;
        Sommet* m_sommet1;
        Sommet* m_sommet2;
};


#endif // ARETE_H_INCLUDED
