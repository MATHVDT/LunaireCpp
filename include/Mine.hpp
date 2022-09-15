/**
 * @file Mine.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Mine
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __MINE_HPP__
#define __MINE_HPP__

#include <fstream>
#include <exception>
#include <math.h>

// #include <iostream>
// #include <list>
// #include <queue>
// #include <SFML/System/Vector2.hpp>
// #include <SFML/Graphics.hpp>
// #include <SFML/Graphics/Rect.hpp>

#include "EnumTypeSol.hpp"
#include "EnumTypeRessource.hpp"
#include "correspondance.hpp"

#include "Batiment.hpp"
#include "ContextGlobal.hpp"

using namespace std;
using namespace sf;

extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesMines;

class Mine : public Batiment
{
private:
    uint _idMine;
    TYPE_SOL _typeSol;
    IntRect _zoomTexture;

public: // Static
    static uint _nbMines;
    static uint _idMaxMines;

    static uint _levelMax;
    static uint _nbAnim;

    static uint _tailleTexture;
    static Texture *_texturesMines[NB_MINES];
    static uint _offsetTextureX; // Largeur d'1 Texture
    static uint _offsetTextureY; // Hauteur

public: // Static
    static uint getNbMines();
    static uint getIdMaxMines();
    static uint getNbAnimMines();
    static uint getLevelMaxMines();

    static void chargerMemoireMines();
    static void dechargerMemoireMines();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Mine(const Vector2u &pos,
         TYPE_SOL typeSol = TYPE_SOL::Vierge);
    virtual ~Mine() override;

    // Virtual
    virtual void init();

    virtual void dessiner(float scaleSprite) override;
    virtual void setTextureRessourceCraft(TYPE_RESSOURCE ressCraft) override;

    virtual void remplirStock() override;
    // virtual TYPE_RESSOURCE livrerStock() override;

    // Gestion des structures connectées
    virtual bool checkConnexionPossible(Structure *s, bool commeSortie) override;

    // Getter
    TYPE_SOL getTypeSol() const;

    // Setter
    void setSpriteTexture(uint tick);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Mine::getNbMines() { return _nbMines; }
inline uint Mine::getIdMaxMines() { return _idMaxMines; }

inline uint Mine::getNbAnimMines() { return _nbAnim; }
inline uint Mine::getLevelMaxMines() { return _levelMax; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline TYPE_SOL Mine::getTypeSol() const { return _typeSol; }

#endif