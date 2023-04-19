/**
 * @file Atelier.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Atelier
 *
 * @version 0.1
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __ATELIER_HPP__
#define __ATELIER_HPP__

#include "ContextGlobal.hpp"
#include "Batiment.hpp"
#include "EnumTypeRessource.hpp"

class ContextGlobal;
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesAteliers;

using namespace std;
using namespace sf;

class Atelier : public Batiment
{
private:
    uint _idAtelier;
    IntRect _zoomTexture;

public: // Static
    static uint _nbAteliers;
    static uint _idMaxAteliers;

    static uint _levelMax;
    static uint _nbAnim;

    static TYPE_RESSOURCE _premiereRessourceAtelier;
    static uint _tailleTexture;
    static Texture *_texturesAteliers[NB_ATELIERS];
    static uint _offsetTextureX; // Largeur d'1 Texture
    static uint _offsetTextureY; // Hauteur

public: // Static
    static uint getNbAteliers();
    static uint getIdMaxAteliers();
    static uint getNbAnimAteliers();
    static uint getLevelMaxAteliers();
    static TYPE_RESSOURCE getPremiereRessourceAteliers();

    static void chargerMemoireAteliers();
    static void dechargerMemoireAteliers();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Atelier(const Vector2u &pos);
    virtual ~Atelier() ;

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
inline uint Atelier::getNbAteliers() { return _nbAteliers; }
inline uint Atelier::getIdMaxAteliers() { return _idMaxAteliers; }

inline uint Atelier::getNbAnimAteliers() { return _nbAnim; }
inline uint Atelier::getLevelMaxAteliers() { return _levelMax; }
inline TYPE_RESSOURCE Atelier::getPremiereRessourceAteliers() { return _premiereRessourceAtelier; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif