#ifndef __MINE_HPP__
#define __MINE_HPP__

#include <iostream>
#include <fstream>
#include <exception>
#include <math.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "enum_sol.hpp"
#include "Batiment.hpp"

// #include "ContextGlobal.hpp"
// #include "enum_ressource.hpp"

using namespace std;
using namespace sf;

extern ContextGlobal &contextGlobal;

class Mine : public Batiment
{
private:
    uint _id;
    Ressource _type;
    uint _level;
    IntRect _zoomTexture;

private:
    static uint _nbMines;
    static uint _idMaxMines;
    static Texture *_texturesMine[NB_RESSOURCES];
    static uint _offsetTextureX;
    static uint _offsetTextureY;

public:
    static uint getNbMines();
    static uint getIdMaxMines();

public:
    Mine(Vector2f pos, Ressource type);
    virtual ~Mine() override;

    virtual void init() override;

    virtual void dessiner(float scaleSprite);
    virtual void update();

    void chargerTextures(string fichierCheminsTexture);

    // Getter

    // Setter
    void updateSpriteTexture();
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Mine::getNbMines() { return _nbMines; }
inline uint Mine::getIdMaxMines() { return _idMaxMines; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif