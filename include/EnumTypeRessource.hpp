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

const int NB_RESSOURCES_AUTRES =1;

const int NB_RESSOURCES_MINERAIS = 7;         // Mine
const int NB_RESSOURCES_LINGOTS = 7;          // Fonderie
const int NB_RESSOURCES_FABRIQUES = 0;        // Fabrique
const int NB_RESSOURCES_ATELIER = 6;          // Atelier
const int NB_RESSOURCES_CUVES = 0;            // Cuve
const int NB_RESSOURCES_CHANTIER_SPATIAL = 0; // ChantierSpatial

const int NB_RESSOURCES = 30; // Total (Faire la somme de toutes les contantes)

enum class TYPE_RESSOURCE : char
{
    // NB_RESSOURCES_AUTRES
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

    // Apres raffinerie/Fonderie
    LingotRegolite,
    Eau, // LingotGlace
    LingotTitane,
    LingotSilicium,
    LingotFer,
    LingotOr,
    LingotAluminium,
    Helium3, // PoussiereRegolite

    // Ressources issues de la Fabrique
    MateriauxConstruction,
    Puce,
    PuceLuxe,

    // Ressources issues de l'Atelier
    SatelliteFragile1,
    SatelliteFragile2,
    SatelliteFragile3,
    SatelliteRobuste1,
    SatelliteRobuste2,
    SatelliteRobuste3,

    // Ressources issues de Cuve
    GazHydrogene,
    GazOxygene,
    PeroxydeHydrogene,
    LiquideHydrogene,
    LiquideOxygene,
    Carburant1,
    Carburant2,

    // Ressources issues de ChantierSpatial
    VaisseauFragile1,
    VaisseauFragile2,
    VaisseauFragile3,
    VaisseauRobuste1,
    VaisseauRobuste2,
    VaisseauRobuste3,
    VaisseauLuxe

};

#endif