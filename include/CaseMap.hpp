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

#include "EnumTypeSol.hpp"
#include "Structure.hpp"
// #include "Batiment.hpp"
#include "ContextGlobal.hpp"

using namespace std;
using namespace sf;

class Structure;
class Batiment;
class ContextGlobal;

extern ContextGlobal *contextGlobal;

class CaseMap
{

private:
    int _id;
    Vector2u _position; // Position case dans la carte hexagonale (x, y)
    TYPE_SOL _typeSol;
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

private: // Static
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
    CaseMap(Vector2u pos = Vector2u{0, 0});
    ~CaseMap();

    void afficherConsole(ostream &flux = cout);
    void dessiner();

    // Getter
    const Vector2f &getPositionSprite() const;
    const Vector2u &getPositionCarte() const;
    TYPE_SOL getTypeSol() const;
    Structure *getConstruction() const;
    Batiment *getBatiment() const;

    // Setter
    void setPositionCarte(uint x, uint y);
    void setPositionCarte(const Vector2u &pos);
    void setTypeSol(TYPE_SOL typeSol);
    void setSpriteTexture();
    void setSpriteTexture(TYPE_SOL typeSol);

    void setCase(Vector2u position,
                 TYPE_SOL typeSol = TYPE_SOL::Vierge);

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
inline void CaseMap::setPositionCarte(uint x, uint y)
{
    setPositionCarte(Vector2u(x, y));
}

inline void CaseMap::setTypeSol(TYPE_SOL typeSol) { _typeSol = typeSol; }

inline const Vector2f &CaseMap::getPositionSprite() const { return _sprite->getPosition(); }
inline const Vector2u &CaseMap::getPositionCarte() const { return _position; }

inline TYPE_SOL CaseMap::getTypeSol() const { return _typeSol; }

inline void CaseMap::setSpriteTexture()
{
    _sprite->setTexture(*_texturesSol[static_cast<int>(_typeSol)]);
}

inline void CaseMap::setSpriteTexture(TYPE_SOL typeSol)
{
    if (typeSol != _typeSol)
        cerr << "/!\\ Petit pb, demande de prendre la texture du sol " << static_cast<int>(typeSol) << " au lieu de celle du sol " << static_cast<int>(_typeSol) << " défini en attribut" << endl;
    _sprite->setTexture(*_texturesSol[static_cast<int>(typeSol)]);
}

inline Structure *CaseMap::getConstruction() const { return _construction; }
inline Batiment *CaseMap::getBatiment() const { return (Batiment *)_construction; }

#endif