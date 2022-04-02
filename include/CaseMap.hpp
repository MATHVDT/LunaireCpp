#ifndef __CASEMAP_HPP__
#define __CASEMAP_HPP__

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

class CaseMap
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
    static float _coteCaseMap;
    static Texture *_texturesSol[5];
    static float _coteHexagoneRayon;

public:
    static float getTailleCase();
    static void setTailleCase(RenderWindow &window,
                              uint nbLignes, uint nbCcolonnes);
    static void chargerSprites(string fichierCheminsTexture);
    static void dechargerSprites();

public:
    // Case(float x = 0.f, float y = 0.f);
    CaseMap(Vector2f pos = Vector2f{0, 0});
    ~CaseMap();

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

inline float CaseMap::getTailleCase()
{
    return _coteHexagoneRayon;
}

inline void CaseMap::setPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
    _hexagone.setPosition(_position);
    _hexagone.setRadius(_coteHexagoneRayon);
    _sprite->setPosition(_position);
    _sprite->setScale(_coteHexagoneRayon, _coteHexagoneRayon);
}

inline void CaseMap::setPosition(Vector2f pos)
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

inline void CaseMap::setTypeSol(SOL typeSol)
{
    _typeSol = typeSol;
    setSprite();
}

inline Vector2f CaseMap::getPosition() { return _position; }

inline SOL CaseMap::getTypeSol() { return _typeSol; }

inline void CaseMap::setSprite()
{
    _sprite->setTexture(*_texturesSol[static_cast<int>(_typeSol)]);
}

#endif