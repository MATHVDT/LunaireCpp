#ifndef __CONNEXION_T_HPP__
#define __CONNEXION_T_HPP__

#include "direction.hpp"

class Structure;    

struct connexion_t
{
    Structure *structure = nullptr;
    const Vector2i direction = NullDirection;
    bool sortie = false;
};

bool operator==(const connexion_t &cg, const connexion_t &cd);

// Définit dans le fichier Batiment.cpp
extern connexion_t ConnexionNull;

/*************************************************** /
    /*                 Méthodes inline                 */
/***************************************************/
inline bool operator==(const connexion_t &cg, const connexion_t &cd)
{
    return (cg.structure == cd.structure &&
            cg.direction == cd.direction &&
            cg.sortie == cd.sortie);
}

#endif