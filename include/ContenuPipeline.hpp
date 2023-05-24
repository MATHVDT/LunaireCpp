/**
 * @file Pipeline.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe ContenuPipeline
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */

#ifndef __CONTENU_PIPELINE_HPP__
#define __CONTENU_PIPELINE_HPP__

#include <queue>
#include <cstdlib>

#include "EnumTypeRessource.hpp"
#include "direction.hpp"
#include "ContextGlobal.hpp"
#include "IconeManager.hpp"

using namespace std;
using namespace sf;

class ContextGlobal;

extern ContextGlobal *contextGlobal;

class ContenuPipeline
{
private:
    Vector2u _positionCarte; // Position case dans la carte hexagonale (x, y)
    DIRECTION &_dirEntree;
    DIRECTION &_dirSortie;

    Sprite *_sprite;

    queue<TYPE_RESSOURCE> _contenu;

private:                   // Static
    static uint _capacite; // = 5 (entrée + 3 +sortie)

public: // Static
    static uint getCapaciteContenu();

    static void chargerMemoireTypeRessource();
    static void dechargerMemoireTypeRessource();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);
    static Vector2f getVDecalageEcran(DIRECTION dir);

public: // public
    ContenuPipeline(const Vector2u &pos,
                    DIRECTION &dirEntree,
                    DIRECTION &dirSortie);

    void dessiner(float scaleSprite);

    TYPE_RESSOURCE livrerStock(queue<TYPE_RESSOURCE> &stockSortie);
    void remplirStock(queue<TYPE_RESSOURCE> &stockEntree);
    void process();
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/

inline uint ContenuPipeline::getCapaciteContenu() { return _capacite; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif
