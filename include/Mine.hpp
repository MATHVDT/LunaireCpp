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
    Ressource _type;
    uint _level;
    IntRect _zoomTexture;

private:
    static Texture *_texturesMine[NB_RESSOURCES];
    static uint _offsetTextureX; 
    static uint _offsetTextureY; 

public:
    Mine(Vector2f pos, Ressource type);
    virtual ~Mine();

    virtual void init() override;

    virtual void dessiner(float scaleSprite);
    virtual void update(); 

    void chargerTextures(string fichierCheminsTexture);

    // Getter

    // Setter
    void updateSpriteTexture();
};

#endif