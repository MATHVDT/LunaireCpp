/**
 * @file Ressource.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Ressource
 *
 * @version 0.1
 * @date 2022-09-10
 *
 * @copyright Copyright (c) 2022
 */
#include "Ressource.hpp"

string cheminFichierTexturesRessources = "ressource/cheminTextures/cheminTexturesTypeRessource.txt";

uint Ressource::_nbRessources = NB_RESSOURCES;
Texture *Ressource::_textureRessource = nullptr;
Sprite *Ressource::_spriteRessources = nullptr;
IntRect Ressource::_zoomTexture{};

float Ressource::_largeurTextureRessource = 0;
float Ressource::_hauteurTextureRessource = 0;

/***************************************************/
/***************************************************/

void Ressource::chargerMemoireRessources()
{
    cerr << endl
         << "chargerMemoireRessources" << endl;
    chargerTextures(cheminFichierTexturesRessources);

    Vector2u textureSize = _textureRessource->getSize();

    // Pas besoin de ses variables
    // _largeurTextureRessource = (float)(textureSize.x / _nbRessources);
    // _hauteurTextureRessource = (float)textureSize.y;

    _zoomTexture.top = 0;
    _zoomTexture.left = 0;
    _zoomTexture.width = textureSize.x / _nbRessources;
    _zoomTexture.height = textureSize.y;

    _spriteRessources->setTextureRect(_zoomTexture);
}

void Ressource::dechargerMemoireRessources()
{
    cerr << endl
         << "dechargerMemoireRessources" << endl;
    delete _spriteRessources->getTexture();
    delete _spriteRessources;
}

void Ressource::chargerTextures(string fichierCheminsTexture)
{
    string cheminTexture;
    sf::Texture *texture = nullptr;
    Sprite *sprite = nullptr;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        monFlux >> _nbRessources;

        cerr << "Nombre de ressources : " << _nbRessources << endl;

        cerr << "Chargement des textures et sprites des Ressources" << endl;

        // Chemin de l'image texture des textures
        monFlux >> cheminTexture;
        cerr << cheminTexture << endl;

        // Create de la nouvelle texture
        texture = new Texture();
        texture->loadFromFile(cheminTexture);

        _textureRessource = texture;
        _spriteRessources = new Sprite{*texture};

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/***************************************************/
/***************************************************/

void Ressource::dessiner(TYPE_RESSOURCE typeRess,
                         const Vector2f &pos,
                         const Vector2f &scale)
{
    // Choisit la texture associée à la ressource
    _zoomTexture.left = (short)typeRess * _zoomTexture.width;
    // Place le Sprite sur dans l'écran
    _spriteRessources->setPosition(pos);
    // Definit la taille/scale du sprite
    _spriteRessources->setScale(scale);

    contextGlobal->dessinerFenetre(_spriteRessources);
}