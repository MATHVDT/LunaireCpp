/**
 * @file EnumTypeSol.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Enum class les différents types de sol
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __ENUM_TYPE_SOL_HPP__
#define __ENUM_TYPE_SOL_HPP__

const int NB_SOL = 9;

enum class TYPE_SOL
{
    // Gisement
    Vierge = 0, // Gisement poussière régolite
    GisementGlace = 1,
    GisementTitane = 2,
    GisementSilicium = 3,
    GisementFer = 4,
    GisementOr = 5,
    GisementAluminium = 6,

    Trou = -1,
    Montage = -2
};

#endif