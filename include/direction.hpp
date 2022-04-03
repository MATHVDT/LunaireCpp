/**
 * @file direction.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des fonctions sur les directions
 * @details Le terme *direction* est utilisée, mais il s'agit en faite du terme sens, ici direction est à interpreter comme *direction géographique* (suivant les points cardinaux)
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
extern const Vector2i NordOuest;     // ↖ (-1,-1)
extern const Vector2i SudOuest;      // ↙ (-1, 0)
extern const Vector2i Sud;           // ↓ ( 0, 1)
extern const Vector2i SudEst;        // ↘ ( 1, 0)
extern const Vector2i NordEst;       // ↗ ( 1,-1)
extern const Vector2i NullDirection; // X ( 0, 0)

Vector2i directionOpposee(const Vector2i& dir);

#endif
