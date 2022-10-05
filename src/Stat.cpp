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

Stat::Stat()
    :  _pos{0.f,0.f},
      _boxStat{0.f, 0.f, 0.f, 0.f},
      _score(0), 
      _scoreText{}
{
}

Stat::~Stat()
{
}

void Stat::init(const Vector2f &pos,
        float width, float height,
        Font & font)
{
    _pos = pos;
    _boxStat.left = _pos.x;
    _boxStat.top=_pos.y;
    _boxStat.height=height;
    _boxStat.width = width;

    _scoreText.setFont(font);

}

void Stat::dessiner(float scale )
{
    contextGlobal->dessinerFenetre(_scoreText);
}
