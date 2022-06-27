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

#include "EnumTypeRessource.hpp"
#include "direction.hpp"

#include "Structure.hpp"
#include "ContextGlobal.hpp"
#include "Structure.hpp"

using namespace std;
using namespace sf;

class ContextGlobal;
// class Structure;
class Batiment;

extern ContextGlobal *contextGlobal;
extern string cheminFichierTexturesPipelines;

struct orientation
{
    uint type;     // TEXTURE
    uint variante; // OFFSET_TEXTURE
};

class Pipeline : public Structure
{
    // Enum
    enum TEXTURE
    {
        NON_CONNECTE = 0,
        ALL_SORTIE = 1,
        ENTREE_ALL = 2,
        DROIT_VERTICAL = 3,
        ANGLE_LARGE = 4,
        DROIT_OBLIQUE = 5,
        ANGLE_ETROIT = 6,
        NB_TEXTURE = 7
    };
    enum OFFSET_TEXTURE
    {
        // NON_CONNECTE
        A_A = 0,
        // ALL_SORTIE
        A_N = 0,
        A_NO = 1,
        A_SO = 2,
        A_S = 3,
        A_SE = 4,
        A_NE = 5,
        // ENTREE_ALL
        S_A = 0,
        SE_A = 1,
        NE_A = 2,
        N_A = 3,
        NO_A = 4,
        SO_A = 5,
        // DROIT_VERTICAL
        S_N = 0,
        N_S = 1,
        // ANGLE_LARGE
        S_NO = 0,
        S_NE = 1,
        N_SO = 2,
        N_SE = 3,
        // DROIT_OBLIQUE
        SE_NO = 0,
        NO_SE = 1,
        SO_NE = 2,
        NE_SO = 3,
        // ANGLE_ETROIT
        S_SO = 0,
        S_SE = 1,
        N_NO = 2,
        N_NE = 3,

    };

private:
    uint _idPipeline;
    IntRect _zoomTexture;

protected:                                // Static
    static const uint _tailleStockEntree; // = 1
    static const uint _tailleStockSortie; // = 1

private: // Static
    static uint _nbPipelines;
    static uint _idMaxPipelines;

    static uint _levelMax; // = 3
    // static uint _nbAnim;   // = 1

    static uint _tailleTexture;
    static Texture *_texturesPipelines[NB_TEXTURE];
    static uint _offsetTextureX; // Largeur d'1 texture
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

    virtual bool checkConnexionPossible(Structure *s, bool commeSortie) override;

    void adaptationTexture();
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