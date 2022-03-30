/**
 * @file direction.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des fonctions sur les directions.
 * @version 0.1
 * @date 2022-03-30
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef __ENUM_DIRECTION__
#define __ENUM_DIRECTION__



#include <Vector2.hpp>

using namespace sf;

extern const Vector2i Nord;          // ↑ ( 0, -2)
extern const Vector2i NordOuest;     // ↖ (-1, -1)
extern const Vector2i SudOuest;      // ↙ (-1, +1)
extern const Vector2i Sud;           // ↓ ( 0, +2)
extern const Vector2i SudEst;        // ↘ ( 0, +1)
extern const Vector2i NordEst;       // ↗ ( 0, -1)
extern const Vector2i NullDirection; // X ( 0,  0)

#endif
