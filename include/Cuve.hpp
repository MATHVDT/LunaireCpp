/**
 * @file Cuve.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Cuve
 *
 * @version 0.1
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __CUVE_HPP__
#define __CUVE_HPP__

#include "ContextGlobal.hpp"
#include "Batiment.hpp"
#include "EnumTypeRessource.hpp"

class ContextGlobal;
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesCuves;

using namespace std;
using namespace sf;

class Cuve : public Batiment
{
private:
    uint _idCuve;
    IntRect _zoomTexture;

public: // Static
    static uint _nbCuves;
    static uint _idMaxCuves;

    static uint _levelMax;
    static uint _nbAnim;

    static TYPE_RESSOURCE _premiereRessourceCuve;
    static uint _tailleTexture;
    static Texture *_texturesCuves[NB_CUVES];
    static uint _offsetTextureX; // Largeur d'1 Texture
    static uint _offsetTextureY; // Hauteur

public: // Static
    static uint getNbCuves();
    static uint getIdMaxCuves();
    static uint getNbAnimCuves();
    static uint getLevelMaxCuves();
    static TYPE_RESSOURCE getPremiereRessourceCuves();

    static void chargerMemoireCuves();
    static void dechargerMemoireCuves();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Cuve(const Vector2u &pos);
    virtual ~Cuve() override;

    // Virtual
    virtual void init();

    virtual void dessiner(float scaleSprite) override;
    virtual void setTextureRessourceCraft(TYPE_RESSOURCE ressCraft) override;

    // Getter

    // Setter
    void setSpriteTexture(uint tick);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Cuve::getNbCuves() { return _nbCuves; }
inline uint Cuve::getIdMaxCuves() { return _idMaxCuves; }

inline uint Cuve::getNbAnimCuves() { return _nbAnim; }
inline uint Cuve::getLevelMaxCuves() { return _levelMax; }
inline TYPE_RESSOURCE Cuve::getPremiereRessourceCuves() { return _premiereRessourceCuve; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif