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

Stat *Stat::_singleton = nullptr;

Stat::Stat()
    : _pos{0.f, 0.f},
      _boxStat{0.f, 0.f, 0.f, 0.f},
      _score(92553456),
      _scoreText{}
{
}

Stat::~Stat()
{
}

void Stat::init(const Vector2f &pos,
                float width, float height,
                Font &font)
{
    _pos = pos;
    _boxStat.left = _pos.x;
    _boxStat.top = _pos.y;
    _boxStat.height = height;
    _boxStat.width = width;

    _scoreText.setFont(font);
    _scoreText.setCharacterSize(90);
    _scoreText.setString(getScoreText());
    _scoreText.setPosition(_pos);

    // Décalage/centrage du score
    Vector2f decalageScoreText{
        (width-10.f - _scoreText.getGlobalBounds().width) / 2.f,
        (height) / 2.f};

    _scoreText.move(decalageScoreText);
}

void Stat::dessiner(float scale)
{
    contextGlobal->dessinerFenetre(_scoreText);
}

/**
 * @brief Récupère ou crée un instance de la Stat *(patron de singleton)*
 * @warning Penser à delete le singleton
 * @return Stat* - *_singleton*
 */
Stat *Stat::getInstance()
{
    // Pas d'instance créée => alors création
    if (Stat::_singleton == nullptr)
        _singleton = new Stat{};
    return _singleton;
}