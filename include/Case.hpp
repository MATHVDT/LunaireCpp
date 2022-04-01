#ifndef __CASE_HPP__
#define __CASE_HPP__

#include <iostream>
#include <exception>
#include <math.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// class RenderWindow;

class Case
{

private:
    Vector2f _position;
    int _etat;
    CircleShape _hexagone;

    static float _coteHexagoneRayon;

public:
    static int _nb;

public:
    // Case(float x = 0.f, float y = 0.f);
    Case(Vector2f pos = Vector2f{0, 0});
    ~Case();

    void afficherConsole(ostream &flux = cout);
    void afficher(RenderWindow &window);

public:
    // Getter
    void setPosition(float x, float y);
    void setPosition(Vector2f pos);

    static float getTailleCase();

    // Setter
    static void setTailleCase(RenderWindow &window,
                              uint nbLignes, uint nbCcolonnes);
};

/**
 * @brief Défini la taille d'une case => cotés de l'hexagone
 * @warning Semble ne pas être utile car les dimensions sont ajustées en fonction de la taille de la fenêtre
 * @param unit - *tailleEcran*
 * @param int - *nbCase*
 */
inline void Case::setTailleCase(RenderWindow &window,
                                uint nbLignes, uint nbCcolonnes)
{
    // cout << "ecran : " << tailleEcran << ", nb cases : " << nbCase << endl;
    uint minEcran = min(window.getSize().x, window.getSize().y);
    uint maxCases = max(nbLignes, nbCcolonnes);
    // _coteHexagoneRayon = (float)minEcran / ((float)maxCases + 1.5f);
    // cout << "cote : " << _coteHexagoneRayon << endl;
    _coteHexagoneRayon = (float)window.getSize().y / ( (float)nbLignes + 2.f) / (float)(sqrt(3) / 2.f);
}

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
}

inline void Case::setPosition(Vector2f pos)
{
    _position = pos;
    _hexagone.setPosition(_position);
    _hexagone.setRadius(_coteHexagoneRayon);
}

#endif