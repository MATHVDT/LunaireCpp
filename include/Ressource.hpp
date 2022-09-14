/**
 * @file Ressource.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Ressource
 *
 * @version 0.1
 * @date 2022-09-10
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __RESSOURCE_HPP__
#define __RESSOURCE_HPP__

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <cstring>

#include <SFML/Graphics.hpp>

#include "ContextGlobal.hpp"
#include "EnumTypeRessource.hpp"

using namespace std;
using namespace sf;

class ContextGlobal;
extern ContextGlobal *contextGlobal;
extern string cheminFichierTexturesRessources;

class Ressource // Static
{
private: // Static
    static uint _nbRessources;
    static Texture *_textureRessource;
    static Sprite *_spriteRessources;
    static IntRect _zoomTexture;

    static float _largeurTextureRessource;
    static float _hauteurTextureRessource;

public: // Static
    static const uint getNbRessources();
    static const Texture *getTextureRessource();
    static IntRect &getZoomTexture(TYPE_RESSOURCE r);

    static void chargerMemoireRessources();
    static void dechargerMemoireRessources();

    static void dessiner(
        TYPE_RESSOURCE typeRess,
        const Vector2f &pos,
        const Vector2f &scale);

private:
    static void chargerTextures(string fichierCheminsTexture);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/
inline const uint Ressource::getNbRessources() { return _nbRessources; }
inline const Texture *Ressource::getTextureRessource() { return _textureRessource; }
inline IntRect &Ressource::getZoomTexture(TYPE_RESSOURCE r)
{
    _zoomTexture.left = _zoomTexture.width * (short)r;
    return _zoomTexture;
}

#endif