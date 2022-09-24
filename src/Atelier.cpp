/**
 * @file Atelier.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Atelier
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "Atelier.hpp"

string cheminFichierTexturesAteliers = "ressource/cheminTextures/cheminTexturesAteliers.txt";

uint Atelier::_nbAteliers = 0;
uint Atelier::_idMaxAteliers = 0;

uint Atelier::_levelMax = 3;
uint Atelier::_nbAnim = 4;

TYPE_RESSOURCE Atelier::_premiereRessourceAtelier = TYPE_RESSOURCE::LingotRegolite; // Ici lingot

uint Atelier::_tailleTexture = 0;
Texture *Atelier::_texturesAteliers[NB_ATELIERS];

uint Atelier::_offsetTextureX = 100;
uint Atelier::_offsetTextureY = 100;

/**
 * @brief Construct a new Atelier:: Atelier object
 *
 * @param const Vector2u & - *pos*
 * @param TYPE_RESSOURCE - *ressourceSol* Atelierrai correspondant au type de sol
 * @param TYPE_RESSOURCE - *ressourceProduite* Atelierrai
 */
Atelier::Atelier(const Vector2u &pos)
    : Batiment{pos, _texturesAteliers[0]},
      _idAtelier(++_idMaxAteliers),
      _zoomTexture{0, 0, 655, 655}
{
    _nbAteliers++;

    setSpriteTexture(0);
    cerr << "Atelier(), id : " << _idAtelier << endl;
}

void Atelier::init() {}

Atelier::~Atelier()
{
    _nbAteliers--;
    cerr << "~Atelier(), id : " << _idAtelier << endl;
}

/*******************************************************/
/*******************************************************/

void Atelier::chargerMemoireAteliers()
{
    cerr << endl
         << "chargerMemoireAteliers" << endl;
    chargerTextures(cheminFichierTexturesAteliers);
    _offsetTextureX = _tailleTexture / 4;
    _offsetTextureY = _offsetTextureX;
}

void Atelier::dechargerMemoireAteliers()
{
    cerr << endl
         << "dechargerMemoireAteliers" << endl;
    for (int i = 0; i < NB_ATELIERS; ++i)
    {
        delete _texturesAteliers[i];
    }
}

/*******************************************************/

/**
 * @brief Charge les textures des différentes Ateliers en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Atelier::chargerTextures(string fichierCheminsTexture)
{
    string nomFichierTexture[NB_ATELIERS];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Ateliers" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_ATELIERS; ++k)
        {
            // Chemin de l'image texture d'une Atelier
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesAteliers[k] = texture;
        }
        _tailleTexture = texture->getSize().x;

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/*******************************************************/
/*******************************************************/

void Atelier::dessiner(float scaleSprite)
{
    // Décalage animation
    setSpriteTexture(contextGlobal->getCurrentTick());
    _sprite->setTextureRect(_zoomTexture);

    Batiment::dessiner(scaleSprite);
}

/**
 * @brief Zoom la texture de la Atelier en fonction du niveau et de l'animation
 *
 * @param uint - *tick*
 */
void Atelier::setSpriteTexture(uint tick)
{
    _zoomTexture.top = _level * _offsetTextureY;
    _zoomTexture.left = tick * _offsetTextureX;

    _sprite->setTextureRect(_zoomTexture);
}

/**
 * @brief Définie la bonne texture en fonction de la ressource craftée.
 * @details Atelier sans ressource à craft => _textureMines[0]
 * Atelier Regolite => _textureMines[1] ...
 *
 * @param TYPE_RESOOURCE - *ressCraft*
 */
void Atelier::setTextureRessourceCraft(TYPE_RESSOURCE ressCraft)
{
    short indice = (short)ressCraft - (short)_premiereRessourceAtelier + 1;

    _sprite->setTexture(*_texturesAteliers[indice]);
}