/**
 * @file Bouton.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Bouton
 *
 * @version 0.1
 * @date 2022-08-31
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __BOUTON_HPP__
#define __BOUTON_HPP__

#include <iostream>
#include <fstream>

// #include <SFML/Graphics.hpp>

#include "ContextGlobal.hpp"

#include "BoutonEnum.hpp"

class ContextGlobal;
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesBoutons;

using namespace std;
using namespace sf;

class Bouton
{
private:
    Rect<float> _box;
    Sprite *_sprite;
    IntRect _zoomTexture;
    BoutonType _type;
    BoutonState _state;
    GameEvent _action;

public: // Static
    static Texture *_texturesBoutons[NB_BOUTONS];
    // static uint _largeurBouton; // Largeur d'1 Bouton
    // static uint _hauteurBouton; // Hauteur d'1 Bouton

public: // Static
    static void chargerMemoireBoutons();
    static void dechargerMemoireBoutons();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Bouton(const Vector2f &posBouton, BoutonType type,
           BoutonState state = BoutonState::Normal,
           GameEvent gameEvent = GameEvent::AucunGameEvent);
    ~Bouton();

    void dessiner(float scaleSprite = 1.f);

    // Setter
    void setSpriteTexture();
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline void Bouton::setSpriteTexture()
{
    _zoomTexture.top = _state * _box.height;
    _sprite->setTextureRect(_zoomTexture);
}

#endif