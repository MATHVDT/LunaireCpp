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
#include <string>

// #include <SFML/Graphics.hpp>

#include "ContextGlobal.hpp"

#include "EnumBouton.hpp"
#include "EnumGameEvent.hpp"

class ContextGlobal;
extern ContextGlobal *contextGlobal;

// extern string cheminFichierTexturesBoutons;

using namespace std;
using namespace sf;

class Bouton
{
private:
    Rect<float> _box; // Box du bouton sur écran
    Sprite *_sprite;
    Vector2f _scale;
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
    Bouton(const Vector2f &posBouton,
           BoutonType type,
           const Vector2f &scale = Vector2f(1.f, 1.f),
           BoutonState state = BoutonState::Normal,
           GameEvent gameEvent = GameEvent::AucunGameEvent);
    ~Bouton();

    void dessiner(float scaleSprite = 1.f);

    // Getter
    Vector2f getPositionEcran() const;
    bool checkIn(const Vector2f &posEcran) const;
    BoutonType getBoutonType() const;
    BoutonState getState() const;
    GameEvent getAction() const;

    // Setter
    void setSpriteTexture();
    void setPositionEcran(const Vector2f &newPositionEcran);
    void deplacerPositionEcran(const Vector2f &translation);
    void setState(BoutonState state);
    void setScale(const Vector2f &scale);
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
inline Vector2f Bouton::getPositionEcran() const { return Vector2f{_box.left, _box.top}; }
inline bool Bouton::checkIn(const Vector2f &posEcran) const { return _box.contains(posEcran); }
inline BoutonType Bouton::getBoutonType() const { return _type; }

inline BoutonState Bouton::getState() const { return _state; }
inline GameEvent Bouton::getAction() const { return _action; }

inline void Bouton::setSpriteTexture()
{
    _zoomTexture.top = _state * _zoomTexture.height;
    _sprite->setTextureRect(_zoomTexture);
}

inline void Bouton::setState(BoutonState state) { _state = state; }

#endif