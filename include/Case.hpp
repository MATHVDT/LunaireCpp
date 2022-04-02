#ifndef __CASE_HPP__
#define __CASE_HPP__

#include <iostream>
#include <fstream>
#include <exception>
#include <math.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "enum_sol.hpp"

using namespace std;
using namespace sf;

// class RenderWindow;

class Case
{

private:
    Vector2f _position;
    SOL _typeSol;
    CircleShape _hexagone; // A remplacer par texture
    int _id;
    Sprite *_sprite;

    // Static
private:
    static int _nb;
    static float _coteHexagoneRayon;
    static Sprite *_spritesSol[5];

public:
    static float getTailleCase();
    static void setTailleCase(RenderWindow &window,
                              uint nbLignes, uint nbCcolonnes);
    static void chargerSprites(string fichierCheminsTexture);
    static void dechargerSprites();

public:
    // Case(float x = 0.f, float y = 0.f);
    Case(Vector2f pos = Vector2f{0, 0});
    ~Case();

    void afficherConsole(ostream &flux = cout);
    void afficher(RenderWindow &window);

public:
    // Getter
    Vector2f getPosition();
    SOL getTypeSol();

    // Setter
    void setPosition(float x, float y);
    void setPosition(Vector2f pos);
    void setTypeSol(SOL typeSol);
    void setSprite();
    void setCase(Vector2f position,
                 SOL typeSol = SOL::Vierge);
};

inline float Case::getTailleCase()
{
    return _coteHexagoneRayon;
}

inline void Case::setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
    _hexagone.setPosition(_position);
    _hexagone.setRadius(_coteHexagoneRayon);
    _sprite->setPosition(_position);
    _sprite->setScale(_coteHexagoneRayon, _coteHexagoneRayon);
}

inline void Case::setPosition(Vector2f pos)
{
    _position = pos;
    _hexagone.setPosition(_position);
    _hexagone.setRadius(_coteHexagoneRayon);
    if (_sprite != nullptr)
    {
        _sprite->setPosition(_position);
        _sprite->setScale(_coteHexagoneRayon, _coteHexagoneRayon);
    }
}

inline void Case::setTypeSol(SOL typeSol)
{
    _typeSol = typeSol;
    setSprite();
    switch (_typeSol)
    {
    case SOL::Vierge:
        _hexagone.setFillColor(Color::Blue);
        break;
    case SOL::Montage:
        _hexagone.setFillColor(Color::Red);
        break;
    case SOL::Trou:
        _hexagone.setFillColor(Color::Yellow);
        break;
    case SOL::GisementFer:
        _hexagone.setFillColor(Color::Green);
        break;
    default:
        _hexagone.setFillColor(Color::White);
        break;
    }
}

inline Vector2f Case::getPosition() { return _position; }

inline SOL Case::getTypeSol() { return _typeSol; }

inline void Case::setSprite()
{
    _sprite = _spritesSol[static_cast<int>(_typeSol)];
}

#endif