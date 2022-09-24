/**
 * @file Cuve.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Cuve
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "Cuve.hpp"

string cheminFichierTexturesCuves = "ressource/cheminTextures/cheminTexturesCuves.txt";

uint Cuve::_nbCuves = 0;
uint Cuve::_idMaxCuves = 0;

uint Cuve::_levelMax = 3;
uint Cuve::_nbAnim = 4;

TYPE_RESSOURCE Cuve::_premiereRessourceCuve = TYPE_RESSOURCE::LingotRegolite; // Ici lingot

uint Cuve::_tailleTexture = 0;
Texture *Cuve::_texturesCuves[NB_CUVES];

uint Cuve::_offsetTextureX = 100;
uint Cuve::_offsetTextureY = 100;

/**
 * @brief Construct a new Cuve:: Cuve object
 *
 * @param const Vector2u & - *pos*
 * @param TYPE_RESSOURCE - *ressourceSol* Cuverai correspondant au type de sol
 * @param TYPE_RESSOURCE - *ressourceProduite* Cuverai
 */
Cuve::Cuve(const Vector2u &pos)
    : Batiment{pos, _texturesCuves[0]},
      _idCuve(++_idMaxCuves),
      _zoomTexture{0, 0, 655, 655}
{
    _nbCuves++;

    setSpriteTexture(0);
    cerr << "Cuve(), id : " << _idCuve << endl;
}

void Cuve::init() {}

Cuve::~Cuve()
{
    _nbCuves--;
    cerr << "~Cuve(), id : " << _idCuve << endl;
}

/*******************************************************/
/*******************************************************/

void Cuve::chargerMemoireCuves()
{
    cerr << endl
         << "chargerMemoireCuves" << endl;
    chargerTextures(cheminFichierTexturesCuves);
    _offsetTextureX = _tailleTexture / 4;
    _offsetTextureY = _offsetTextureX;
}

void Cuve::dechargerMemoireCuves()
{
    cerr << endl
         << "dechargerMemoireCuves" << endl;
    for (int i = 0; i < NB_CUVES; ++i)
    {
        delete _texturesCuves[i];
    }
}

/*******************************************************/

/**
 * @brief Charge les textures des différentes Cuves en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Cuve::chargerTextures(string fichierCheminsTexture)
{
    string nomFichierTexture[NB_CUVES];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Cuves" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_CUVES; ++k)
        {
            // Chemin de l'image texture d'une Cuve
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesCuves[k] = texture;
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

void Cuve::dessiner(float scaleSprite)
{
    // Décalage animation
    setSpriteTexture(contextGlobal->getCurrentTick());
    _sprite->setTextureRect(_zoomTexture);

    Batiment::dessiner(scaleSprite);
}

/**
 * @brief Zoom la texture de la Cuve en fonction du niveau et de l'animation
 *
 * @param uint - *tick*
 */
void Cuve::setSpriteTexture(uint tick)
{
    _zoomTexture.top = _level * _offsetTextureY;
    _zoomTexture.left = tick * _offsetTextureX;

    _sprite->setTextureRect(_zoomTexture);
}

/**
 * @brief Définie la bonne texture en fonction de la ressource craftée.
 * @details Cuve sans ressource à craft => _textureMines[0]
 * Cuve Regolite => _textureMines[1] ...
 *
 * @param TYPE_RESOOURCE - *ressCraft*
 */
void Cuve::setTextureRessourceCraft(TYPE_RESSOURCE ressCraft)
{
    short indice = (short)ressCraft - (short)_premiereRessourceCuve + 1;

    _sprite->setTexture(*_texturesCuves[indice]);
}