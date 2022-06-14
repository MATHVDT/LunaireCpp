/**
 * @file Pipeline.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Pipeline
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __PIPELINE_HPP__
#define __PIPELINE_HPP__

#include <iostream>
#include <list>
#include <queue>
#include <sys/types.h>
#include <string>

// #include "ContextGlobal.hpp"
#include "EnumTypeRessource.hpp"
#include "direction.hpp"

#include "Structure.hpp"

using namespace std;
using namespace sf;

class ContextGlobal;
// class Structure;

// Initialisation dans main.cpp
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesPipelines;

class Pipeline : public Structure
{

    enum TEXTURE
    {
        NON_RELIE = 0,
        DROIT = 1,
        ANGLE = 2,
        NB_TEXTURE = 3
    };

private:
    uint _idPipeline;
    IntRect _zoomTexture;

protected: // Static
    static const uint _tailleStockEntree;
    static const uint _tailleStockSortie;

private: // Static
    static uint _nbPipelines;
    static uint _idMaxPipelines;

    static uint _levelMax; // = 3
    // static uint _nbAnim;   // = 1

    static uint _tailleTexture;
    static Texture *_texturesPipelines[NB_TEXTURE];
    static uint _offsetTextureY; // Hauteur d'1 texture

public: // Static
    static uint getNbPipelines();
    static uint getIdMaxPipelines();
    static uint getLevelMaxPipelines();

    static uint getTailleStockEntree();
    static uint getTailleStockSortie();

    static void chargerMemoirePipelines();
    static void dechargerMemoirePipelines();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Pipeline();
    Pipeline(const Vector2u &pos);
    virtual ~Pipeline();

    virtual void init() override;

    virtual void dessiner(float scaleSprite) override;
    virtual void update() override;
    virtual void process() override;

    // Getter
    uint getIdPipeline() const;

    // Setter
    void setSpriteTexture(uint tick);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Pipeline::getNbPipelines() { return _nbPipelines; }
inline uint Pipeline::getIdMaxPipelines() { return _idMaxPipelines; }
inline uint Pipeline::getLevelMaxPipelines() { return _levelMax; }

inline uint Pipeline::getTailleStockEntree() { return _tailleStockEntree; }
inline uint Pipeline::getTailleStockSortie() { return _tailleStockSortie; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif