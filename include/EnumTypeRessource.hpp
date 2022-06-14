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

// #define NB_RESSOURCES 5;
const uint NB_RESSOURCES = 5;

enum class TYPE_RESSOURCE
{
    // Matières premières
    PoussiereRegolite=0,
    MineraiGlace,
    MineraiTitane,
    MineraiSilicium,
    MineraiFer,
 
    Rien,

    MineraiAluminium,
    MineraiMagnesium,
    MineraiCalcium,
    MineraiSoduim,

    // Apres raffinerie
    LingotRegolite,
    LingotGlace,
    LingotTitane,
    LingotSilicium,
    LingotFer,

    LingotAluminium,
    LingotMagnesium,
    LingotCalcium,
    LingotSoduim,

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