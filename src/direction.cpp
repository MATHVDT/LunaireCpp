/**
 * @file direction.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implementation des fonctions sur les directions.
 * @warning Gestion des directions changées, certaines fonctions sont deprecated
 * 
 * 
 * @version 0.1
 * @date 2022-03-30
 *
 * @copyright Copyright (c) 2022
 */
#include "direction.hpp"

// Deprecated NE PAS UTILISER
const Vector2i Nord{0, -1};         // Dir. principale ↑ ( 0, -1)
const Vector2i NordOuest{-1, -1};   // Dir. principale ↖ (-1, -1)
const Vector2i SudOuest{-1, 0};     // Dir. principale ↙ (-1, 0)
const Vector2i Sud{0, 1};           // Dir. principale ↓ ( 0, 1)
const Vector2i SudEst{1, 0};        // Dir. principale ↘ (1, 0)
const Vector2i NordEst{1, -1};      // Dir. principale ↗ ( 1, -1)
const Vector2i NullDirection{0, 0}; // Dir. principale X ( 0,  0)

/**
 * @deprecated Changement de gestion des directions
 * @brief Donne le vecteur de sens opposé
 *
 * @param const Vector2i & - *dir*
 * @return const Vector2i& - *direction opposée*
 */
Vector2i directionOpposee(const Vector2i &dir)
{
    Vector2i dirOpposee;
    if (dir == Nord)
        dirOpposee = Sud;
    else if (dir == NordOuest)
        dirOpposee = SudEst;
    else if (dir == SudOuest)
        dirOpposee = NordEst;
    else if (dir == Sud)
        dirOpposee = Nord;
    else if (dir == SudEst)
        dirOpposee = NordOuest;
    else if (dir == NordEst)
        dirOpposee = SudOuest;
    else if (dir == NullDirection)
        dirOpposee = NullDirection;
    else
        dirOpposee = NullDirection;

    return dirOpposee;
}

/**
 * @deprecated Changement de gestion des directions
 * @brief Transforme un entier (qui représente un direction dans une tab[6]) en vecteur direction
 *
 * @param int - *dirInt* (indice dans un tab[6])
 * @return const Vector2i& - *dirVector*
 */
Vector2i directionIntToVecteur(int dirInt)
{
    Vector2i dirVector;
    switch (dirInt)
    {
    case NORD:
        dirVector = Nord;
        break;
    case NORDOUEST:
        dirVector = NordOuest;
        break;
    case SUDOUEST:
        dirVector = SudOuest;
        break;
    case SUD:
        dirVector = Sud;
        break;
    case SUDEST:
        dirVector = SudEst;
        break;
    case NORDEST:
        dirVector = NordEst;
        break;
    default:
        dirVector = NullDirection;
        break;
    }
    return dirVector;
}

/**
 * @deprecated Changement de gestion des directions
 * @brief Transforme une direction en un entier qui correspond à l'indice de la direction dans un tab[6]
 *
 * @param const Vector2i & - *dirVecteur*
 * @return int - *indice d'une direction dans un tab[6]*
 */
int directionVecteurToInt(const Vector2i &dirVecteur)
{
    int dirInt;
    if (dirVecteur == Nord)
        dirInt = NORD;
    else if (dirVecteur == NordOuest)
        dirInt = NORDOUEST;
    else if (dirVecteur == SudOuest)
        dirInt = SUDEST;
    else if (dirVecteur == Sud)
        dirInt = SUD;
    else if (dirVecteur == SudEst)
        dirInt = SUDEST;
    else if (dirVecteur == NordEst)
        dirInt = NORDEST;
    else
        dirInt = NULLDIRECTION;

    return dirInt;
}

/********************************************************/

Vector2i positionCaseVoisine(const Vector2i &posCaseCarte,
                             int dirEnum)
{
    Vector2i posCaseVoisine;

    switch (dirEnum)
    {
    case NORD:
        posCaseVoisine =
            positionCaseVoisineNORD(posCaseCarte);
        break;
    case NORDOUEST:
        posCaseVoisine =
            positionCaseVoisineNORDOUEST(posCaseCarte);
        break;
    case SUDOUEST:
        posCaseVoisine =
            positionCaseVoisineSUDOUEST(posCaseCarte);
        break;
    case SUD:
        posCaseVoisine =
            positionCaseVoisineSUD(posCaseCarte);
        break;
    case SUDEST:
        posCaseVoisine =
            positionCaseVoisineSUDEST(posCaseCarte);
        break;
    case NORDEST:
        posCaseVoisine =
            positionCaseVoisineNORDEST(posCaseCarte);
        break;
    case NULLDIRECTION:
    default:
        posCaseVoisine =
            positionCaseVoisineNULLDIRECTION(posCaseCarte);
        break;
    }
    return posCaseVoisine;
}

Vector2i positionCaseVoisineNORD(const Vector2i &posCaseCarte)
{
    return posCaseCarte + Vector2i(0, -1);
}

Vector2i positionCaseVoisineNORDOUEST(const Vector2i &posCaseCarte)
{
    return posCaseCarte +
           Vector2i(-1, -1 * (posCaseCarte.x % 2));
}

Vector2i positionCaseVoisineSUDOUEST(const Vector2i &posCaseCarte)
{
    return posCaseCarte +
           Vector2i(-1, 1 - (posCaseCarte.x % 2));
}

Vector2i positionCaseVoisineSUD(const Vector2i &posCaseCarte)
{
    return posCaseCarte + Vector2i(0, 1);
}

Vector2i positionCaseVoisineSUDEST(const Vector2i &posCaseCarte)
{
    return posCaseCarte +
           Vector2i(1, 1 - (posCaseCarte.x % 2));
}

Vector2i positionCaseVoisineNORDEST(const Vector2i &posCaseCarte)
{
    return posCaseCarte +
           Vector2i(1, -1 * (posCaseCarte.x % 2));
}

Vector2i positionCaseVoisineNULLDIRECTION(const Vector2i &posCaseCarte)
{
    return posCaseCarte + Vector2i(0, 0);
}
