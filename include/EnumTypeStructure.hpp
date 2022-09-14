#ifndef __ENUM_TYPE_STRUCTURE__HPP
#define __ENUM_TYPE_STRUCTURE__HPP

const int NB_MINES = 8;
const int NB_FONDERIES = 8;

enum class TYPE_STRUCTURE : int
{
    AucuneStructure = -1,
    Pipeline = 0,
    Marchand = 1,
    Mine = 2,
    Fonderie = 3,
    Fabrique = 4,
    Atelier = 5,
    Cuve = 6,
    ChantierSpatial = 7,

    MasterBatiment,

    // Mines
    MinePoussiereRegolite,
    MineGlace,
    MineTitane,
    MineSilicium,
    MineFer,
    MineOr,
    MineAluminium,
    MineMagnesium
    // MineCalcium,
    // MineSoduim
};

#endif