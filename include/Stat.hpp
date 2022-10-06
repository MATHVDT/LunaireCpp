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
#include <iostream>

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

public: // Static
    static Stat *_singleton;

public: // Static
    static Stat *getInstance();

public:
    ~Stat();

    void init(const Vector2f &pos,
              float width, float height,
              Font &font);

    void dessiner(float scale = 1.f);

    // Getter
    int getScore() const;
    string getScoreText() const;
    const Vector2f &getPosition() const;

    // Setter
    void setScore(int val);
    void incScore(int valInc = 1);
    void translater(const Vector2f &translation);

private:
    Stat();
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
// Getter
inline int Stat::getScore() const { return _score; }
inline string Stat::getScoreText() const { return to_string(_score); }
inline const Vector2f &Stat::getPosition() const { return _pos; }

// Setter
inline void Stat::setScore(int val) { _score = val; }
inline void Stat::incScore(int valInc) { _score += valInc; }

inline void Stat::translater(const Vector2f &translation)
{
    _pos.x += translation.x;
    _pos.y += translation.y;
    _boxStat.left = _pos.x;
    _boxStat.top = _pos.y;
    // _scoreText.setPosition(_scoreText.getPosition() + translation);
    _scoreText.move(translation);

}

#endif