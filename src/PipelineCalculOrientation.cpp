#include "Pipeline.hpp"

bool Pipeline::calculOrientation(
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
        return true;
    }

    // ENTREE_ALL (juste une entrée)
    if (calculOrientationEntreeAll(dirEntree, dirSortie))
        return true;

    // ALL_SORTIE (juste une sortie)
    if (calculOrientationAllSortie(dirEntree, dirSortie))
        return true;

    // ANGLE_LARGE
    if (calculOrientationAngleLarge(dirEntree, dirSortie))
        return true;

    // ANGLE_ETROIT
    if (calculOrientationAngleEtroit(dirEntree, dirSortie))
        return true;

    // DROIT_VERTICAL
    if (calculOrientationDroitVertical(dirEntree, dirSortie))
        return true;

    // DROIT_OBLIQUE
    if (calculOrientationDroiteOblique(dirEntree, dirSortie))
        return true;

    cerr << "Erreur par d'orientation trouvée pour le Pipeline de direction et sens : " << dirEntree << "->" << dirSortie << endl;

    return false;
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
    }
    if (_orientation.type == ENTREE_ALL)
        return true;
    else
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
    }
    if (_orientation.type == ALL_SORTIE)
        return true;
    else
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
    else if (dirEntree == DIRECTION::NORDOUEST)
    {
        if (dirSortie == DIRECTION::SUD)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = NO_S;
        }
        else if (dirSortie == DIRECTION::NORDEST)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = NO_NE;
        }
    }
    else if (dirEntree == DIRECTION::NORDEST)
    {
        if (dirSortie == DIRECTION::SUD)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = NE_S;
        }
        else if (dirSortie == DIRECTION::NORDOUEST)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = NE_NO;
        }
    }
    else if (dirEntree == DIRECTION::SUDEST)
    {
        if (dirSortie == DIRECTION::NORD)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = SE_N;
        }
        else if (dirSortie == DIRECTION::SUDOUEST)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = SE_SO;
        }
    }
    else if (dirEntree == DIRECTION::SUDOUEST)
    {
        if (dirSortie == DIRECTION::NORD)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = SO_N;
        }
        else if (dirSortie == DIRECTION::SUDEST)
        {
            _orientation.type = ANGLE_LARGE;
            _orientation.variant = SO_SE;
        }
    }

    // Pas un ANGLE_LARGE
    if (_orientation.type == ANGLE_LARGE)
        return true;
    else
        return false;
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
    else if (dirEntree == DIRECTION::SUDOUEST)
    {
        if (dirSortie == DIRECTION::SUD)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = SO_S;
        }
        else if (dirSortie == DIRECTION::NORDOUEST)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = SO_NO;
        }
    }
    else if (dirEntree == DIRECTION::SUDEST)
    {
        if (dirSortie == DIRECTION::SUD)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = SE_S;
        }
        else if (dirSortie == DIRECTION::NORDEST)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = SE_NE;
        }
    }
    else if (dirEntree == DIRECTION::NORDOUEST)
    {
        if (dirSortie == DIRECTION::SUDOUEST)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = NO_SO;
        }
        else if (dirSortie == DIRECTION::NORD)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = NO_N;
        }
    }
    else if (dirEntree == DIRECTION::NORDEST)
    {
        if (dirSortie == DIRECTION::SUDEST)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = NE_SE;
        }
        else if (dirSortie == DIRECTION::NORD)
        {
            _orientation.type = ANGLE_ETROIT;
            _orientation.variant = NE_N;
        }
    }

    // Pas un ANGLE_ETROIT
    if (_orientation.type == ANGLE_ETROIT)
        return true;
    else
        return false;
}

// DROIT_VERTICAL
bool Pipeline::calculOrientationDroitVertical(
    DIRECTION dirEntree, DIRECTION dirSortie)
{
    if (dirEntree == DIRECTION::SUD &&
        dirSortie == DIRECTION::NORD)
    {
        _orientation.type = DROIT_VERTICAL;
        _orientation.variant = S_N;
    }
    else if (dirEntree == DIRECTION::NORD &&
             dirSortie == DIRECTION::SUD)
    {
        _orientation.type = DROIT_VERTICAL;
        _orientation.variant = N_S;
    }

    // Pas un DROIT_VERTICAL
    if (_orientation.type == DROIT_VERTICAL)
        return true;
    else
        return false;
}

// DROIT_OBLIQUE
bool Pipeline::calculOrientationDroiteOblique(
    DIRECTION dirEntree, DIRECTION dirSortie)
{
    if (dirEntree == DIRECTION::SUDEST &&
        dirSortie == DIRECTION::NORDOUEST)
    {
        _orientation.type = DROIT_OBLIQUE;
        _orientation.variant = SE_NO;
    }
    else if (dirEntree == DIRECTION::NORDOUEST &&
             dirSortie == DIRECTION::SUDEST)
    {
        _orientation.type = DROIT_OBLIQUE;
        _orientation.variant = NO_SE;
    }
    else if (dirEntree == DIRECTION::SUDOUEST &&
             dirSortie == DIRECTION::NORDEST)
    {
        _orientation.type = DROIT_OBLIQUE;
        _orientation.variant = SO_NE;
    }
    else if (dirEntree == DIRECTION::NORDEST &&
             dirSortie == DIRECTION::SUDOUEST)
    {
        _orientation.type = DROIT_OBLIQUE;
        _orientation.variant = NE_SO;
    }

    // Pas un DROIT_OBLIQUE
    if (_orientation.type == DROIT_OBLIQUE)
        return true;
    else
        return false;
}