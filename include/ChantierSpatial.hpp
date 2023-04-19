/**
 * @file ChantierSpatial.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe ChantierSpatial
 *
 * @version 0.1
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __CHANTIER_SPATIAL_HPP__
#define __CHANTIER_SPATIAL_HPP__

#include "ContextGlobal.hpp"
#include "Batiment.hpp"
#include "EnumTypeRessource.hpp"

class ContextGlobal;
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesChantierSpatials;

using namespace std;
using namespace sf;

class ChantierSpatial : public Batiment
{
private:
    uint _idChantierSpatial;
    IntRect _zoomTexture;

public: // Static
    static uint _nbChantierSpatials;
    static uint _idMaxChantierSpatials;

    static uint _levelMax;
    static uint _nbAnim;

    static TYPE_RESSOURCE _premiereRessourceChantierSpatial;
    static uint _tailleTexture;
    static Texture *_texturesChantierSpatials[NB_CHANTIER_SPATIALS];
    static uint _offsetTextureX; // Largeur d'1 Texture
    static uint _offsetTextureY; // Hauteur

public: // Static
    static uint getNbChantierSpatials();
    static uint getIdMaxChantierSpatials();
    static uint getNbAnimChantierSpatials();
    static uint getLevelMaxChantierSpatials();
    static TYPE_RESSOURCE getPremiereRessourceChantierSpatials();

    static void chargerMemoireChantierSpatials();
    static void dechargerMemoireChantierSpatials();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    ChantierSpatial(const Vector2u &pos);
    virtual ~ChantierSpatial() ;

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
inline uint ChantierSpatial::getNbChantierSpatials() { return _nbChantierSpatials; }
inline uint ChantierSpatial::getIdMaxChantierSpatials() { return _idMaxChantierSpatials; }

inline uint ChantierSpatial::getNbAnimChantierSpatials() { return _nbAnim; }
inline uint ChantierSpatial::getLevelMaxChantierSpatials() { return _levelMax; }
inline TYPE_RESSOURCE ChantierSpatial::getPremiereRessourceChantierSpatials() { return _premiereRessourceChantierSpatial; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif