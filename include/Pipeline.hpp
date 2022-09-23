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
#include <stack>
#include <sys/types.h>
#include <string>

#include "EnumTypeRessource.hpp"
#include "direction.hpp"

#include "Structure.hpp"
#include "ContextGlobal.hpp"
#include "Structure.hpp"
#include "ContenuPipeline.hpp"

using namespace std;
using namespace sf;

class ContextGlobal;
// class Structure;
class Batiment;

extern ContextGlobal *contextGlobal;
extern string cheminFichierTexturesPipelines;

struct Orientation_t
{
    DIRECTION dirEntree;
    DIRECTION dirSortie;
    uint type;    // TEXTURE
    uint variant; // OFFSET_TEXTURE
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
        NO_S = 4,
        NE_S = 5,
        SO_N = 6,
        SE_N = 7,
        NO_NE = 8,
        NE_NO = 9,
        SO_SE = 10,
        SE_SO = 11,
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
        SO_S = 4,
        SE_S = 5,
        NO_N = 6,
        NE_N = 7,
        SO_NO = 8,
        NO_SO = 9,
        SE_NE = 10,
        NE_SE = 11,
    };

private:
    uint _idPipeline;
    IntRect _zoomTexture;
    Orientation_t _orientation;
    ContenuPipeline _contenuPipeline;

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

    static void chargerMemoirePipelines();
    static void dechargerMemoirePipelines();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Pipeline();
    Pipeline(const Vector2u &pos);
    virtual ~Pipeline();

    virtual void init();

    virtual void dessiner(float scaleSprite) override;
    virtual void process();

    virtual bool updateOrientation() override;
    virtual bool checkConnexionPossible(Structure *s, bool commeSortie) override;

    // TYPE_RESSOURCE livrerStock();
    // virtual void remplirStock();

    // Gestion des structures connectées
    virtual bool connecterStructure(Structure *s, bool commeSortie = true, bool connexionAutreSens = false) override;
    virtual bool deconnecterStructure(Structure *s) override;

    // Getter
    uint getIdPipeline() const;
    Structure *getStructureEntreePipeline() const;

    // Setter
    void setSpriteTexture(uint tick);

    bool calculOrientation(DIRECTION dirEntree, DIRECTION dirSortie);
    bool calculOrientationEntreeAll(DIRECTION dirEntree, DIRECTION dirSortie);
    bool calculOrientationAllSortie(DIRECTION dirEntree, DIRECTION dirSortie);
    bool calculOrientationAngleLarge(DIRECTION dirEntree, DIRECTION dirSortie);
    bool calculOrientationAngleEtroit(DIRECTION dirEntree, DIRECTION dirSortie);
    bool calculOrientationDroitVertical(DIRECTION dirEntree, DIRECTION dirSortie);
    bool calculOrientationDroiteOblique(DIRECTION dirEntree, DIRECTION dirSortie);

    bool inverserSens();
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

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline Structure *Pipeline::getStructureEntreePipeline() const
{
    for (auto &c : _connexions)
    {
        if (c.type == TypeConnexion::Input)
            return c.structure;
    }
    return nullptr;
}

#endif