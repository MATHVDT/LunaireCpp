/**
 * @file Fabrique.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Fabrique
 *
 * @version 0.1
 * @date 2022-09-05
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __FABRIQUE_HPP__
#define __FABRIQUE_HPP__

#include "ContextGlobal.hpp"
#include "Batiment.hpp"
#include "EnumTypeRessource.hpp"

class ContextGlobal;
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesFabriques;

using namespace std;
using namespace sf;

class Fabrique : public Batiment
{
private:
    uint _idFabrique;
    IntRect _zoomTexture;

public: // Static
    static uint _nbFabriques;
    static uint _idMaxFabriques;

    static uint _levelMax;
    static uint _nbAnim;

    static TYPE_RESSOURCE _premiereRessourceFabrique;
    static uint _tailleTexture;
    static Texture *_texturesFabriques[NB_FABRIQUES];
    static uint _offsetTextureX; // Largeur d'1 Texture
    static uint _offsetTextureY; // Hauteur

public: // Static
    static uint getNbFabriques();
    static uint getIdMaxFabriques();
    static uint getNbAnimFabriques();
    static uint getLevelMaxFabriques();
    static TYPE_RESSOURCE getPremiereRessourceFabriques();

    static void chargerMemoireFabriques();
    static void dechargerMemoireFabriques();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Fabrique(const Vector2u &pos);
    virtual ~Fabrique() ;

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
inline uint Fabrique::getNbFabriques() { return _nbFabriques; }
inline uint Fabrique::getIdMaxFabriques() { return _idMaxFabriques; }

inline uint Fabrique::getNbAnimFabriques() { return _nbAnim; }
inline uint Fabrique::getLevelMaxFabriques() { return _levelMax; }
inline TYPE_RESSOURCE Fabrique::getPremiereRessourceFabriques() { return _premiereRessourceFabrique; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif