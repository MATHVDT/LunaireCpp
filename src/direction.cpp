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

const Vector2i Nord{0, -2};         // Dir. principale ↑ ( 0, -2)
const Vector2i NordOuest{-1, -1};   // Dir. principale ↖ (-1, -1)
const Vector2i SudOuest{-1, +1};    // Dir. principale ↙ (-1, +1)
const Vector2i Sud{0, +2};          // Dir. principale ↓ ( 0, +2)
const Vector2i SudEst{0, +1};       // Dir. principale ↘ ( 0, +1)
const Vector2i NordEst{0, -1};      // Dir. principale ↗ ( 0, -1)
const Vector2i NullDirection{0, 0}; // Dir. principale X ( 0,  0)
