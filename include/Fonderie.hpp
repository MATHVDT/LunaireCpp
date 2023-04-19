/**
 * @file Fonderie.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Fonderie
 *
 * @version 0.1
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __FONDERIE_HPP__
#define __FONDERIE_HPP__

#include "ContextGlobal.hpp"
#include "Batiment.hpp"
#include "EnumTypeRessource.hpp"

class ContextGlobal;
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesFonderies;

using namespace std;
using namespace sf;

class Fonderie : public Batiment
{
private:
    uint _idFonderie;
    IntRect _zoomTexture;

public: // Static
    static uint _nbFonderies;
    static uint _idMaxFonderies;

    static uint _levelMax;
    static uint _nbAnim;

    static TYPE_RESSOURCE _premiereRessourceFonderie;
    static uint _tailleTexture;
    static Texture *_texturesFonderies[NB_FONDERIES];
    static uint _offsetTextureX; // Largeur d'1 Texture
    static uint _offsetTextureY; // Hauteur

public: // Static
    static uint getNbFonderies();
    static uint getIdMaxFonderies();
    static uint getNbAnimFonderies();
    static uint getLevelMaxFonderies();
    static TYPE_RESSOURCE getPremiereRessourceFonderies();

    static void chargerMemoireFonderies();
    static void dechargerMemoireFonderies();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Fonderie(const Vector2u &pos);
    virtual ~Fonderie();

    // Virtual
    virtual void init();
    virtual bool updateOrientation() override { return Batiment::updateOrientation(); }


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
inline uint Fonderie::getNbFonderies() { return _nbFonderies; }
inline uint Fonderie::getIdMaxFonderies() { return _idMaxFonderies; }

inline uint Fonderie::getNbAnimFonderies() { return _nbAnim; }
inline uint Fonderie::getLevelMaxFonderies() { return _levelMax; }
inline TYPE_RESSOURCE Fonderie::getPremiereRessourceFonderies() { return _premiereRessourceFonderie; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif