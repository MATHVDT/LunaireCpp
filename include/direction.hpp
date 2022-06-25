/**
 * @file direction.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des fonctions sur les directions
 * @details Le terme *direction* est utilisée, mais il s'agit en faite du terme sens, ici direction est à interpreter comme *direction géographique* (suivant les points cardinaux)
 * @warning Gestion des directions changées, certaines fonctions sont deprecated
 *
 * @version 0.1
 * @date 2022-03-30
 *
 * @copyright Copyright (c) 2022
 */

#ifndef __ENUM_DIRECTION__
#define __ENUM_DIRECTION__

#include <SFML/System/Vector2.hpp>

using namespace sf;

// Vector2i = (x , y)

extern const Vector2i Nord;          // ↑ ( 0,-1)
extern const Vector2i NordOuest;     // ↖ (-1,-1) si x%2 == 1 ou (-1, 0) si x%2 == 0
extern const Vector2i SudOuest;      // ↙ (-1, 0) si x%2 == 1 ou (-1,+1) si x%2 == 0
extern const Vector2i Sud;           // ↓ ( 0, 1)
extern const Vector2i SudEst;        // ↘ ( 1, 0) si x%2 == 1 ou (+1,+1) si x%2 == 0
extern const Vector2i NordEst;       // ↗ ( 1,-1) si x%1 == 1 ou (+1, 0) si x%2 == 0
extern const Vector2i NullDirection; // X ( 0, 0)

Vector2i directionOpposee(const Vector2i &dir);
Vector2i directionIntToVecteur(int dirInt);
int directionVecteurToInt(const Vector2i &dirVecteur);

enum DIRECTION
{
    NORD = 0,      // ↑
    NORDOUEST = 1, // ↖
    // OUEST,      // ←
    SUDOUEST = 2, // ↙
    SUD = 3,      // ↓
    SUDEST = 4,   // ↘
    // EST,        // →
    NORDEST = 5,       // ↗
    NULLDIRECTION = -1 // X
};

Vector2i positionCaseVoisine(const Vector2i &posCaseCarte, int dirEnum);
Vector2i positionCaseVoisine(const Vector2u &posCaseCarte, int dirEnum);

/*******************************************************/
/*******************************************************/

Vector2i positionCaseVoisineNORD(const Vector2i &posCaseCarte);
Vector2i positionCaseVoisineNORDOUEST(const Vector2i &posCaseCarte);
Vector2i positionCaseVoisineSUDOUEST(const Vector2i &posCaseCarte);
Vector2i positionCaseVoisineSUD(const Vector2i &posCaseCarte);
Vector2i positionCaseVoisineSUDEST(const Vector2i &posCaseCarte);
Vector2i positionCaseVoisineNORDEST(const Vector2i &posCaseCarte);
Vector2i positionCaseVoisineNULLDIRECTION(const Vector2i &posCaseCarte);

/*******************************************************/

Vector2u positionCaseVoisineNORD(const Vector2u &posCaseCarte);
Vector2u positionCaseVoisineNORDOUEST(const Vector2u &posCaseCarte);
Vector2u positionCaseVoisineSUDOUEST(const Vector2u &posCaseCarte);
Vector2u positionCaseVoisineSUD(const Vector2u &posCaseCarte);
Vector2u positionCaseVoisineSUDEST(const Vector2u &posCaseCarte);
Vector2u positionCaseVoisineNORDEST(const Vector2u &posCaseCarte);
Vector2u positionCaseVoisineNULLDIRECTION(const Vector2u &posCaseCarte);

/*******************************************************/

DIRECTION positionOrigineDestToDirection(const Vector2i &origine, const Vector2i &dest);
DIRECTION positionOrigineDestToDirection(const Vector2u &origine, const Vector2u &dest);

/*******************************************************/
/*******************************************************/

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/
inline Vector2i positionCaseVoisine(const Vector2u &posCaseCarte, int dirEnum)
{
    return positionCaseVoisine((Vector2i)posCaseCarte, dirEnum);
}
inline Vector2u positionCaseVoisineNORD(const Vector2u &posCaseCarte)
{
    return positionCaseVoisineNORD((Vector2u)posCaseCarte);
}
inline Vector2u positionCaseVoisineNORDOUEST(const Vector2u &posCaseCarte)
{
    return positionCaseVoisineNORDOUEST((Vector2u)posCaseCarte);
}
inline Vector2u positionCaseVoisineSUDOUEST(const Vector2u &posCaseCarte)
{
    return positionCaseVoisineSUDOUEST((Vector2u)posCaseCarte);
}
inline Vector2u positionCaseVoisineSUD(const Vector2u &posCaseCarte)
{
    return positionCaseVoisineSUD((Vector2u)posCaseCarte);
}
inline Vector2u positionCaseVoisineSUDEST(const Vector2u &posCaseCarte)
{
    return positionCaseVoisineSUDEST((Vector2u)posCaseCarte);
}
inline Vector2u positionCaseVoisineNORDEST(const Vector2u &posCaseCarte)
{
    return positionCaseVoisineNORDEST((Vector2u)posCaseCarte);
}
inline Vector2u positionCaseVoisineNULLDIRECTION(const Vector2u &posCaseCarte)
{
    return positionCaseVoisineNULLDIRECTION((Vector2u)posCaseCarte);
}

/*******************************************************/

inline DIRECTION positionOrigineDestToDirection(const Vector2u &origine, const Vector2u &dest)
{
    return positionOrigineDestToDirection((Vector2u)origine, (Vector2u)dest);
}

#endif
