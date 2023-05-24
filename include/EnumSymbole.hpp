/**
 * @file EnumSymbole.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Enum class pour les différents types de ressources
 *
 * @version 0.1
 * @date 2023-04-26
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __ENUM_SYMBOLE_HPP__
#define __ENUM_SYMBOLE_HPP__

#include <sys/types.h>

const int NB_SYMBOLES = 7;

enum class SYMBOLE : char
{
    FlecheGauche,
    FlecheDroite,
    FlecheHaut,
    FlecheBas,
    Plus,
    Moins,
    Egale
};

#endif
