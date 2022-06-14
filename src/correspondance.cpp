#include "correspondance.hpp"

/**
 * @brief Donne le type de ressource associée à un type de sol
 *
 * @param TYPE_SOL - *sol*
 * @return TYPE_RESSOURCE - *ressource*
 */
TYPE_RESSOURCE typeSolToTypeRessource(TYPE_SOL sol)
{
    TYPE_RESSOURCE ress = TYPE_RESSOURCE::Rien;
    switch (sol)
    {
    case TYPE_SOL::Vierge:
        ress = TYPE_RESSOURCE::PoussiereRegolite;
        break;
    case TYPE_SOL::GisementGlace:
        ress = TYPE_RESSOURCE::MineraiGlace;
        break;
    case TYPE_SOL::GisementTitane:
        ress = TYPE_RESSOURCE::MineraiTitane;
        break;
    case TYPE_SOL::GisementSilicium:
        ress = TYPE_RESSOURCE::MineraiSilicium;
        break;
    case TYPE_SOL::GisementFer:
        ress = TYPE_RESSOURCE::MineraiFer;
        break;
    case TYPE_SOL::GisementOr:
        ress = TYPE_RESSOURCE::MineraiOr;
        break;
    case TYPE_SOL::GisementAluminium:
        ress = TYPE_RESSOURCE::MineraiAluminium;
        break;
    case TYPE_SOL::GisementMagnesium:
        ress = TYPE_RESSOURCE::MineraiMagnesium;
        break;
    case TYPE_SOL::GisementCalcium:
        ress = TYPE_RESSOURCE::MineraiCalcium;
        break;
    case TYPE_SOL::GisementSoduim:
        ress = TYPE_RESSOURCE::MineraiSoduim;
        break;
    default:
        break;
    }

    return ress;
}

/**
 * @brief Donne le type de ressource associée à un type de structure
 *
 * @param TYPE_STRUCTURE - *structure*
 * @return TYPE_RESSOURCE - *ressource*
 */
TYPE_RESSOURCE typeStructureToTypeRessource(TYPE_STRUCTURE structure)
{
    TYPE_RESSOURCE ress = TYPE_RESSOURCE::Rien;

    switch (structure)
    {
    case TYPE_STRUCTURE::Mine: // Par defaut regolite
    case TYPE_STRUCTURE::MinePoussiereRegolite:
        ress = TYPE_RESSOURCE::PoussiereRegolite;
        break;
    case TYPE_STRUCTURE::MineGlace:
        ress = TYPE_RESSOURCE::MineraiGlace;
        break;
    case TYPE_STRUCTURE::MineTitane:
        ress = TYPE_RESSOURCE::MineraiTitane;
        break;
    case TYPE_STRUCTURE::MineSilicium:
        ress = TYPE_RESSOURCE::MineraiSilicium;
        break;
    case TYPE_STRUCTURE::MineFer:
        ress = TYPE_RESSOURCE::MineraiFer;
        break;
    case TYPE_STRUCTURE::MineOr:
        ress = TYPE_RESSOURCE::MineraiOr;
        break;
    case TYPE_STRUCTURE::MineAluminium:
        ress = TYPE_RESSOURCE::MineraiAluminium;
        break;
    case TYPE_STRUCTURE::MineMagnesium:
        ress = TYPE_RESSOURCE::MineraiMagnesium;
        break;
    case TYPE_STRUCTURE::MineCalcium:
        ress = TYPE_RESSOURCE::MineraiCalcium;
        break;
    case TYPE_STRUCTURE::MineSoduim:
        ress = TYPE_RESSOURCE::MineraiSoduim;
        break;
    default:
        break;
    }

    return ress;
}

/**
 * @brief Donne le type de structure associée à un type de ressource
 *
 * @param TYPE_RESSOURCE - *ressource*
 * @return TYPE_STRUCTURE - *structure*
 */
TYPE_STRUCTURE typeStructureToTypeRessource(TYPE_RESSOURCE ressource)
{
    TYPE_STRUCTURE structure = TYPE_STRUCTURE::AucuneStructure;

    switch (ressource)
    {
    case TYPE_RESSOURCE::Rien: // Par defaut regolite
    case TYPE_RESSOURCE::PoussiereRegolite:
        structure = TYPE_STRUCTURE::MinePoussiereRegolite;

        break;
    case TYPE_RESSOURCE::MineraiGlace:
        structure = TYPE_STRUCTURE::MineGlace;

        break;
    case TYPE_RESSOURCE::MineraiTitane:
        structure = TYPE_STRUCTURE::MineTitane;
        ;
        break;
    case TYPE_RESSOURCE::MineraiSilicium:
        structure = TYPE_STRUCTURE::MineSilicium;
        break;
    case TYPE_RESSOURCE::MineraiFer:
        structure = TYPE_STRUCTURE::MineFer;
        break;
    case TYPE_RESSOURCE::MineraiOr:
        structure = TYPE_STRUCTURE::MineOr;
        break;
    case TYPE_RESSOURCE::MineraiAluminium:
        structure = TYPE_STRUCTURE::MineAluminium;
        break;
    case TYPE_RESSOURCE::MineraiMagnesium:
        structure = TYPE_STRUCTURE::MineMagnesium;
        break;
    case TYPE_RESSOURCE::MineraiCalcium:
        structure = TYPE_STRUCTURE::MineCalcium;
        break;
    case TYPE_RESSOURCE::MineraiSoduim:
        structure = TYPE_STRUCTURE::MineSoduim;
        ;
        break;
    default:
        break;
    }

    return structure;
}