/**
 * @file enum_ressource.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Enum class pour les différents types de ressources
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __ENUM_TYPE_RESSOURCE_HPP__
#define __ENUM_TYPE_RESSOURCE_HPP__

#include <sys/types.h>

// #define NB_RESSOURCES 5;
const uint NB_RESSOURCES = 5;
const uint NB_RESSOURCES_MINERAIS = 5;
const uint NB_RESSOURCES_LINGOTS = 7;

enum class TYPE_RESSOURCE : char
{
    Rien = 0,
    // Gisement
    Vierge, // Gisement poussière régolite
    GisementGlace,
    GisementTitane,
    GisementSilicium,
    GisementFer,
    GisementOr,
    GisementAluminium,

    // Matières premières
    PoussiereRegolite,
    MineraiGlace,
    MineraiTitane,
    MineraiSilicium,
    MineraiFer,
    MineraiOr,
    MineraiAluminium,

    // MineraiMagnesium,
    // MineraiCalcium,
    // MineraiSoduim,

    // Apres raffinerie
    LingotRegolite,
    LingotGlace,
    LingotTitane,
    LingotSilicium,
    LingotFer,
    LingotOr,
    LingotAluminium,

    // LingotMagnesium,
    // LingotCalcium,
    // LingotSoduim,

    Helium3, // PoussiereRegolite

    // A partir de la glace
    HydrogeneGaz,
    OxygeneGaz,

    HydrogeneLiquide,
    OxygeneLiquide,
    PeroxydeHydrogene, // HydrogeneGaz + OxygeneGaz,

    Caburant1,  // HydrogeneLiquide + OxygeneLiquide
    Carburant2, // PeroxydeHydrogene

    MateriauxConstruction, // LingotRegolite
    Puce,                  // LingotSilicium

    Satellite, // MateriauxConstruction + LingotSilicium
    Vaisseau,  // MateriauxConstruction + LingotSilicium

};

#endif