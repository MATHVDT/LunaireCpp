#ifndef __ENUM_SOL_HPP__
#define __ENUM_SOL_HPP__

#define NB_RESSOURCES 5;

enum RESSOURCE
{
    // Matières premères
    PoussiereRegolite,
    MineraiGlace,
    MineraiTitane,
    MineraiSilicium,
    MineraiFer,

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