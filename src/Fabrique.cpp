/**
 * @file Fabrique.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Fabrique
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "Fabrique.hpp"

string cheminFichierTexturesFabriques = "ressource/cheminTextures/cheminTexturesFabriques.txt";

uint Fabrique::_nbFabriques = 0;
uint Fabrique::_idMaxFabriques = 0;

uint Fabrique::_levelMax = 3;
uint Fabrique::_nbAnim = 4;

TYPE_RESSOURCE Fabrique::_premiereRessourceFabrique = TYPE_RESSOURCE::LingotRegolite; // Ici lingot

uint Fabrique::_tailleTexture = 0;
Texture *Fabrique::_texturesFabriques[NB_FABRIQUES];

uint Fabrique::_offsetTextureX = 100;
uint Fabrique::_offsetTextureY = 100;

/**
 * @brief Construct a new Fabrique:: Fabrique object
 *
 * @param const Vector2u & - *pos*
 * @param TYPE_RESSOURCE - *ressourceSol* Fabriquerai correspondant au type de sol
 * @param TYPE_RESSOURCE - *ressourceProduite* Fabriquerai
 */
Fabrique::Fabrique(const Vector2u &pos)
    : Batiment{pos, _texturesFabriques[0]},
      _idFabrique(++_idMaxFabriques),
      _zoomTexture{0, 0, 655, 655}
{
    _nbFabriques++;

    setSpriteTexture(0);
    cerr << "Fabrique(), id : " << _idFabrique << endl;
}

void Fabrique::init() {}

Fabrique::~Fabrique()
{
    _nbFabriques--;
    cerr << "~Fabrique(), id : " << _idFabrique << endl;
}

/*******************************************************/
/*******************************************************/

void Fabrique::chargerMemoireFabriques()
{
    cerr << endl
         << "chargerMemoireFabriques" << endl;
    chargerTextures(cheminFichierTexturesFabriques);
    _offsetTextureX = _tailleTexture / 4;
    _offsetTextureY = _offsetTextureX;
}

void Fabrique::dechargerMemoireFabriques()
{
    cerr << endl
         << "dechargerMemoireFabriques" << endl;
    for (int i = 0; i < NB_FABRIQUES; ++i)
    {
        delete _texturesFabriques[i];
    }
}

/*******************************************************/

/**
 * @brief Charge les textures des différentes Fabriques en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Fabrique::chargerTextures(string fichierCheminsTexture)
{
    string nomFichierTexture[NB_FABRIQUES];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Fabriques" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_FABRIQUES; ++k)
        {
            // Chemin de l'image texture d'une Fabrique
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesFabriques[k] = texture;
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

void Fabrique::dessiner(float scaleSprite)
{
    // Décalage animation
    setSpriteTexture(contextGlobal->getCurrentTick());
    _sprite->setTextureRect(_zoomTexture);

    Batiment::dessiner(scaleSprite);
}

/**
 * @brief Zoom la texture de la Fabrique en fonction du niveau et de l'animation
 *
 * @param uint - *tick*
 */
void Fabrique::setSpriteTexture(uint tick)
{
    _zoomTexture.top = _level * _offsetTextureY;
    _zoomTexture.left = tick * _offsetTextureX;

    _sprite->setTextureRect(_zoomTexture);
}

/**
 * @brief Définie la bonne texture en fonction de la ressource craftée.
 * @details Fabrique sans ressource à craft => _textureMines[0]
 * Fabrique Regolite => _textureMines[1] ...
 *
 * @param TYPE_RESOOURCE - *ressCraft*
 */
void Fabrique::setTextureRessourceCraft(TYPE_RESSOURCE ressCraft)
{
    short indice = (short)ressCraft - (short)_premiereRessourceFabrique + 1;

    _sprite->setTexture(*_texturesFabriques[indice]);
}