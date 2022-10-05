/**
 * @file Stat.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Stat
 *
 * @version 0.1
 * @date 2022-09-28
 *
 * @copyright Copyright (c) 2022
 */

#ifndef __STAT_H__
#define __STAT_H__

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "EnumTypeRessource.hpp"

#include "ContextGlobal.hpp"

// struct (TYPE_RESSOURCE, isDejaVendu, isEnProduction)

class ContextGlobal;

// using namespace std;
using std::cout;
using std::endl;
using namespace sf;

extern ContextGlobal *contextGlobal;

class Stat
{
private:
    Vector2f _pos;
    Rect<float> _boxStat;
    RectangleShape _boxStatShape; // ??_pos??

    int _score;
    Text _scoreText;

public:
    Stat();
    ~Stat();

    void init(const Vector2f &pos,
              float width, float height,
              Font &font);

    void dessiner(float scale = 1.f);
};

#endif // __STAT_H__