#include "Pipeline.hpp"

void Pipeline::calculOrientation(
    DIRECTION dirEntree, DIRECTION dirSortie)
{
    // Par defaut
    _orientation.type = NON_CONNECTE;
    _orientation.variant = A_A;

    // NON_CONNECTE (aucune sortie)
    if (dirEntree == DIRECTION::NULLDIRECTION &&
        dirSortie == DIRECTION::NULLDIRECTION)
    {
        _orientation.type = NON_CONNECTE;
        _orientation.variant = A_A;
        return;
    }

    // ENTREE_ALL (juste une entrée)
    if (!calculOrientationEntreeAll(dirEntree, dirSortie))
        return;

    // ALL_SORTIE (juste une sortie)
    if (!calculOrientationAllSortie(dirEntree, dirSortie))
        return;

    // ANGLE_LARGE
    if (!calculOrientationAngleLarge(dirEntree, dirSortie))
        return;

    // ANGLE_ETROIT
    if (!calculOrientationAngleEtroit(dirEntree, dirSortie))
        return;

    // DROIT_VERTICAL
    if (!calculOrientationDroitVertical(dirEntree, dirSortie))
        return;

    // DROIT_OBLIQUE
    if (!calculOrientationDroiteOblique(dirEntree, dirSortie))
        return;
}

/*******************************************************/

// ENTREE_ALL (juste une entrée)
bool Pipeline::calculOrientationEntreeAll(
    DIRECTION dirEntree, DIRECTION dirSortie)
{
    if (dirSortie == DIRECTION::NULLDIRECTION)
    {
        switch (dirEntree)
        {
        case DIRECTION::NORD:
            _orientation.type = ENTREE_ALL;
            _orientation.variant = N_A;
            break;
        case DIRECTION::NORDOUEST:
            _orientation.type = ENTREE_ALL;
            _orientation.variant = NO_A;
            break;
        case DIRECTION::SUDOUEST:
            _orientation.type = ENTREE_ALL;
            _orientation.variant = SO_A;
            break;
            break;
        case DIRECTION::SUD:
            _orientation.type = ENTREE_ALL;
            _orientation.variant = S_A;
            break;
        case DIRECTION::NORDEST:
            _orientation.type = ENTREE_ALL;
            _orientation.variant = NE_A;
            break;
        case DIRECTION::SUDEST:
            _orientation.type = ENTREE_ALL;
            _orientation.variant = SE_A;
        }
        return true;
    }
    return false;
}

// ALL_SORTIE (juste une sortie)
bool Pipeline::calculOrientationAllSortie(
    DIRECTION dirEntree, DIRECTION dirSortie)
{
    if (dirEntree == DIRECTION::NULLDIRECTION)
    {
        switch (dirSortie)
        {
        case DIRECTION::NORD:
            _orientation.type = ALL_SORTIE;
            _orientation.variant = A_N;
            break;
        case DIRECTION::NORDOUEST:
            _orientation.type = ALL_SORTIE;
            _orientation.variant = A_NO;
            break;
        case DIRECTION::SUDOUEST:
            _orientation.type = ALL_SORTIE;
            _orientation.variant = A_SO;
            break;
            break;
        case DIRECTION::SUD:
            _orientation.type = ALL_SORTIE;
            _orientation.variant = A_S;
            break;
        case DIRECTION::NORDEST:
            _orientation.type = ALL_SORTIE;
            _orientation.variant = A_NE;
            break;
        case DIRECTION::SUDEST:
            _orientation.type = ALL_SORTIE;
            _orientation.variant = A_SE;
        }
        return true;
    }
    return false;
}

// ANGLE_LARGE
bool Pipeline::calculOrientationAngleLarge(
    DIRECTION dirEntree, DIRECTION dirSortie)
{
    if (dirEntree == DIRECTION::SUD)
    {
        if (dirSortie == DIRECTION::NORDOUEST)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = S_NO;
        }
        else if (dirSortie == DIRECTION::NORDEST)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = S_NE;
        }
    }
    else if (dirEntree == DIRECTION::NORD)
    {
        if (dirSortie == DIRECTION::SUDOUEST)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = N_SO;
        }
        else if (dirSortie == DIRECTION::SUDEST)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = N_SE;
        }
    }
    else
    { // Pas un ANGLE_LARGE
        return false;
    }
    return true;
}

// ANGLE_ETROIT
bool Pipeline::calculOrientationAngleEtroit(
    DIRECTION dirEntree, DIRECTION dirSortie)
{
    if (dirEntree == DIRECTION::SUD)
    {
        if (dirSortie == DIRECTION::SUDOUEST)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = S_SO;
        }
        else if (dirSortie == DIRECTION::SUDEST)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = S_SE;
        }
    }
    else if (dirEntree == DIRECTION::NORD)
    {
        if (dirSortie == DIRECTION::NORDOUEST)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = N_NO;
        }
        else if (dirSortie == DIRECTION::NORDEST)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = N_NE;
        }
    }
    else
    { // Pas un ANGLE_ETROIT
        return false;
    }
    return true;
}

// DROIT_VERTICAL
bool Pipeline::calculOrientationDroitVertical(
    DIRECTION dirEntree, DIRECTION dirSortie)
{
}

// DROIT_OBLIQUE
bool Pipeline::calculOrientationDroiteOblique(
    DIRECTION dirEntree, DIRECTION dirSortie)
{
}