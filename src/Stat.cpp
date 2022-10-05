/**
 * @file Stat.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Stat
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */

#include "Stat.hpp"

Stat::Stat(const Vector2f &pos, float width, float height)
    : // _pos{},
      _boxStat{pos.x, pos.y, width, height},
      _score(0)
{
}

Stat::~Stat()
{
}

void Stat::dessiner(float scale )
{
    //constext
}
