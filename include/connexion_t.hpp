/**
 * @file connexion_t.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief
 * @deprecated Changement de la gestion des connexions, liste des structures connectées
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __CONNEXION_T_HPP__
#define __CONNEXION_T_HPP__

#include "direction.hpp"
#include "Structure.hpp"

class Structure;

enum class TypeConnexion
{
    Input,
    Output,
    Blocked,
    SealOff, // Condamné
    Undefined
};

struct connexion_t
{
    Structure *structure = nullptr;
    DIRECTION direction = DIRECTION::NULLDIRECTION;
    TypeConnexion type = TypeConnexion::Undefined;
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
            cg.type == cd.type);
}

#endif