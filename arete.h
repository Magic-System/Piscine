#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include "sommet.h"

class Arete
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Arete(std::string, Sommet*, Sommet*, std::vector<float>);

        void afficherArete()    const;
        std::string getId() const;

        Sommet* getsommet1() const
        {
            return m_sommet1;
        }

        Sommet* getsommet2() const
        {
            return m_sommet2;
        }

        std::vector<float> getpoids() const
        {
            return m_poids;
        }

        ~Arete();

    protected:

    private:
        std::string m_id;
        std::vector<float> m_poids;
        Sommet* m_sommet1;
        Sommet* m_sommet2;
};


#endif // ARETE_H_INCLUDED
