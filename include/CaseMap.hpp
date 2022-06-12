/**
 * @file CaseMap.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe CaseMap
 * 
 * @version 0.1
 * @date 2022-06-09
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef __CASEMAP_HPP__
#define __CASEMAP_HPP__

#include <iostream>
#include <fstream>
#include <exception>
#include <math.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "enum_sol.hpp"
// #include "ContextGlobal.hpp"
#include "Structure.hpp"

using namespace std;
using namespace sf;

class ContextGlobal;
class Structure;

// Initialisation dans main.cpp
extern ContextGlobal *contextGlobal;

class CaseMap
{

private:
    int _id;
    Vector2f _position;
    SOL _typeSol;
    Sprite *_sprite;
    Structure *_construction;

private: // Static
    static int _nb;
    static float _tailleCaseMap;
    static float _scaleCaseMap;
    static uint _tailleTexture;
    static Texture *_texturesSol[5];
    static float _coteHexagoneRayon;

public: // Static
    static void chargerMemoireCaseMap();
    static void dechargerMemoireCaseMap();

        private : // Static
                  static void chargerSprites(string fichierCheminsTexture);
    static void dechargerSprites();

public:
    static float getTailleCaseMap();
    static float getScaleCaseMap();
    static float getTailleTexture();
    static void setScaleCaseMap(
        uint nbLignesCarte,
        uint nbCcolonnesCarte);

public:
    // Case(float x = 0.f, float y = 0.f);
    CaseMap(Vector2f pos = Vector2f{0, 0});
    ~CaseMap();

    void afficherConsole(ostream &flux = cout);
    void dessiner();

    // Getter
    const Vector2f &getPosition() const;
    SOL getTypeSol() const;
    Structure *getConstruction() const;

    // Setter
    void setPosition(float x, float y);
    void setPosition(const Vector2f &pos);
    void setTypeSol(SOL typeSol);
    void setSpriteTexture();
    void setSpriteTexture(SOL typeSol);

    void setCase(Vector2f position,
                 SOL typeSol = SOL::Vierge);

    void ajouterConstruction(Structure *s);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline float CaseMap::getTailleCaseMap() { return _tailleCaseMap; }
inline float CaseMap::getScaleCaseMap() { return _scaleCaseMap; }
inline float CaseMap::getTailleTexture() { return _tailleTexture; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline void CaseMap::setPosition(float x, float y)
{
    setPosition(Vector2f(x, y));
}

inline void CaseMap::setPosition(const Vector2f &pos)
{
    _position = pos;
    _sprite->setPosition(_position);
}

inline void CaseMap::setTypeSol(SOL typeSol) { _typeSol = typeSol; }

inline const Vector2f &CaseMap::getPosition() const { return _position; }

inline SOL CaseMap::getTypeSol() const { return _typeSol; }

inline void CaseMap::setSpriteTexture()
{
    _sprite->setTexture(*_texturesSol[static_cast<int>(_typeSol)]);
}

inline void CaseMap::setSpriteTexture(SOL typeSol)
{
    if (typeSol != _typeSol)
        cerr << "/!\\ Petit pb, demande de prendre la texture du sol " << static_cast<int>(typeSol) << " au lieu de celle du sol " << static_cast<int>(_typeSol) << " défini en attribut" << endl;
    _sprite->setTexture(*_texturesSol[static_cast<int>(typeSol)]);
}

inline Structure *CaseMap::getConstruction() const { return _construction; }

#endif