/**
 * @file Fonderie.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Fonderie
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "Fonderie.hpp"

string cheminFichierTexturesFonderies = "ressource/cheminTextures/cheminTexturesFonderies.txt";

uint Fonderie::_nbFonderies = 0;
uint Fonderie::_idMaxFonderies = 0;

uint Fonderie::_levelMax = 3;
uint Fonderie::_nbAnim = 4;

uint Fonderie::_tailleTexture = 0;
Texture *Fonderie::_texturesFonderies[NB_RESSOURCES_LINGOTS];

uint Fonderie::_offsetTextureX = 100;
uint Fonderie::_offsetTextureY = 100;

/**
 * @brief Construct a new Fonderie:: Fonderie object
 *
 * @param const Vector2u & - *pos*
 * @param TYPE_RESSOURCE - *ressourceSol* Fonderierai correspondant au type de sol
 * @param TYPE_RESSOURCE - *ressourceProduite* Fonderierai
 */
Fonderie::Fonderie(const Vector2u &pos,
                   TYPE_RESSOURCE ressourceProduite)
    : Batiment{pos, _texturesFonderies[static_cast<int>(ressourceProduite)]},
      _idFonderie(++_idMaxFonderies),
      _typeRessourceProduite(ressourceProduite),
      _zoomTexture{0, 0, 655, 655}
{
    _nbFonderies++;

    setSpriteTexture(0);
    cerr << "Fonderie(), id : " << _idFonderie << endl;
}

void Fonderie::init() {}

Fonderie::~Fonderie()
{
    _nbFonderies--;
    cerr << "~Fonderie(), id : " << _idFonderie << endl;
}

/*******************************************************/
/*******************************************************/

void Fonderie::chargerMemoireFonderies()
{
    cerr << endl
         << "chargerMemoireFonderies" << endl;
    chargerTextures(cheminFichierTexturesFonderies);
    _offsetTextureX = _tailleTexture / 4;
    _offsetTextureY = _offsetTextureX;
}

void Fonderie::dechargerMemoireFonderies()
{
    cerr << endl
         << "dechargerMemoireFonderies" << endl;
    for (int i = 0; i < NB_RESSOURCES_LINGOTS; ++i)
    {
        delete _texturesFonderies[i];
    }
}

/**
 * @brief Charge les textures des différentes Fonderies en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Fonderie::chargerTextures(string fichierCheminsTexture)
{
    string nomFichierTexture[NB_RESSOURCES_LINGOTS];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Fonderies" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_RESSOURCES_LINGOTS; ++k)
        {
            // Chemin de l'image texture d'une Fonderie
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesFonderies[k] = texture;
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

void Fonderie::dessiner(float scaleSprite)
{
    // Décalage animation
    setSpriteTexture(contextGlobal->getCurrentTick());
    _sprite->setTextureRect(_zoomTexture);

    Batiment::dessiner(scaleSprite);
}

/**
 * @brief Zoom la texture de la Fonderie en fonction du niveau et de l'animation
 *
 * @param uint - *tick*
 */
void Fonderie::setSpriteTexture(uint tick)
{
    _zoomTexture.top = _level * _offsetTextureY;
    _zoomTexture.left = tick * _offsetTextureX;

    _sprite->setTextureRect(_zoomTexture);
}

void Fonderie::update() {}
void Fonderie::process() {}
void Fonderie::remplirStock() {}

/**
 * @brief Définie la bonne texture en fonction de la ressource craftée.
 * @details Fonderie sans ressource à craft => _textureMines[0]
 * Fonderie Regolite => _textureMines[1] ...
 *
 * @param TYPE_RESOOURCE - *ressCraft*
 */
void Fonderie::setTextureRessourceCraft(TYPE_RESSOURCE ressCraft)
{
    TYPE_RESSOURCE premiereRessource = TYPE_RESSOURCE::LingotRegolite; // Ici lingot
    short indice = (short)ressCraft - (short)premiereRessource + 1;

    _sprite->setTexture(*_texturesFonderies[indice]);
}