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

extern string cheminFichierTexturesBoutons;

using namespace std;
using namespace sf;

class Fonderie : public Batiment
{
private:
    uint _idFonderie;
    TYPE_RESSOURCE _typeRessourceProduite;
    IntRect _zoomTexture;

public: // Static
    static uint _nbFonderies;
    static uint _idMaxFonderies;

    static uint _levelMax;
    static uint _nbAnim;

    static uint _tailleTexture;
    static Texture *_texturesFonderies[NB_RESSOURCES_LINGOTS];
    static uint _offsetTextureX; // Largeur d'1 Texture
    static uint _offsetTextureY; // Hauteur

public: // Static
    static uint getNbFonderies();
    static uint getIdMaxFonderies();
    static uint getNbAnimFonderies();
    static uint getLevelMaxFonderies();

    static void chargerMemoireFonderies();
    static void dechargerMemoireFonderies();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Fonderie(const Vector2u &pos,
             TYPE_RESSOURCE ressourceProduite = TYPE_RESSOURCE::Rien);
    virtual ~Fonderie() override;

    virtual void init() override; // Va pas servir a mon avis

    virtual void dessiner(float scaleSprite);
    virtual void update() override;

    // Getter
    TYPE_RESSOURCE getTypeRessource() const;

    // Setter
    void setSpriteTexture(uint tick);
    virtual void setTextureRessourceCraft(TYPE_RESSOURCE ressCraft) override;

    virtual void process() override;
    virtual void remplirStock() override;
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

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline TYPE_RESSOURCE Fonderie::getTypeRessource() const { return _typeRessourceProduite; }

#endif