/**
 * @file IconeManager.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe IconeManager
 *
 * @version 0.1
 * @date 2022-09-10
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __ICONE_MANAGER_HPP__
#define __ICONE_MANAGER_HPP__

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <cstring>

#include <SFML/Graphics.hpp>

#include "ContextGlobal.hpp"
#include "EnumTypeRessource.hpp"
#include "EnumSymbole.hpp"

using namespace std;
using namespace sf;

class ContextGlobal;
extern ContextGlobal *contextGlobal;
extern string cheminFichierTexturesRessources;
extern string cheminFichierTexturesSymboles;

class IconeManager // Static
{
private: // Static
    static IntRect _zoomTexture;
    static float _largeurTextureIcone;
    static float _hauteurTextureIcone;

    // Ressource
    static uint _nbRessources;
    static Texture *_texturesRessource;
    static Sprite *_spritesRessource;

    // Symbole
    static uint _nbSymboles;
    static Texture *_texturesSymbole;
    static Sprite *_spritesSymbole;

public: // Static
    static void chargerMemoireIcones();
    static void dechargerMemoireIcones();

    // Ressource
    static const uint getNbRessources();
    static const Texture *getTexturesRessource();
    static IntRect &getZoomTextureRessource(TYPE_RESSOURCE r);

    // Symbole
    static const uint getNbSymboles();
    static const Texture *getTexturesSymbole();
    static IntRect &getZoomTextureSymbole(SYMBOLE s);

    static void dessiner(
        TYPE_RESSOURCE typeRess,
        const Vector2f &pos,
        const Vector2f &scale);

    static void dessiner(
        SYMBOLE symbole,
        const Vector2f &pos,
        const Vector2f &scale);

private:
    static void chargerTextures(string fichierCheminsTexture,
                                Texture *&texture,
                                Sprite *&spritesTab,
                                uint &quantiteIcone);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/
// Ressource
inline const uint IconeManager::getNbRessources() { return _nbRessources; }
inline const Texture *IconeManager::getTexturesRessource() { return _texturesRessource; }
inline IntRect &IconeManager::getZoomTextureRessource(TYPE_RESSOURCE r)
{
    _zoomTexture.left = _zoomTexture.width * (short)r;
    return _zoomTexture;
}

// Symbole
inline const uint IconeManager::getNbSymboles() { return _nbSymboles; }
inline const Texture *IconeManager::getTexturesSymbole() { return _texturesSymbole; }
inline IntRect &IconeManager::getZoomTextureSymbole(SYMBOLE s)
{
    _zoomTexture.left = _zoomTexture.width * (short)s;
    return _zoomTexture;
}
#endif