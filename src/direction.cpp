/**
 * @file direction.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implementation des fonctions sur les directions.
 * @version 0.1
 * @date 2022-03-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "direction.hpp"

const Vector2i Nord{0, -1};         // Dir. principale ↑ ( 0, -1)
const Vector2i NordOuest{-1, -1};   // Dir. principale ↖ (-1, -1)
const Vector2i SudOuest{-1, 0};     // Dir. principale ↙ (-1, 0)
const Vector2i Sud{0, 1};           // Dir. principale ↓ ( 0, 1)
const Vector2i SudEst{1, 0};        // Dir. principale ↘ (1, 0)
const Vector2i NordEst{1, -1};      // Dir. principale ↗ ( 1, -1)
const Vector2i NullDirection{0, 0}; // Dir. principale X ( 0,  0)

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
