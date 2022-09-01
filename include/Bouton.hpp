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

#include <SFML/Graphics.hpp>

#include "BoutonEnum.hpp"
#include "ContextGlobal.hpp"

class ContextGlobal;

using namespace std;
using namespace sf;

extern string cheminFichierTexturesBoutons;

class Bouton
{
private:
    Rect<int> _box;
    Sprite *_sprite;
    GameEvent _action;
    BoutonType _type;
    BoutonState _state;

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
    Bouton(/* args */);
    ~Bouton();

    void dessiner(float scaleSprite);
};

#endif