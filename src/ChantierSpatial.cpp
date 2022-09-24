/**
 * @file ChantierSpatial.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe ChantierSpatial
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "ChantierSpatial.hpp"

string cheminFichierTexturesChantierSpatials = "ressource/cheminTextures/cheminTexturesChantierSpatials.txt";

uint ChantierSpatial::_nbChantierSpatials = 0;
uint ChantierSpatial::_idMaxChantierSpatials = 0;

uint ChantierSpatial::_levelMax = 3;
uint ChantierSpatial::_nbAnim = 4;

TYPE_RESSOURCE ChantierSpatial::_premiereRessourceChantierSpatial = TYPE_RESSOURCE::LingotRegolite; // Ici lingot

uint ChantierSpatial::_tailleTexture = 0;
Texture *ChantierSpatial::_texturesChantierSpatials[NB_CHANTIER_SPATIALS];

uint ChantierSpatial::_offsetTextureX = 100;
uint ChantierSpatial::_offsetTextureY = 100;

/**
 * @brief Construct a new ChantierSpatial:: ChantierSpatial object
 *
 * @param const Vector2u & - *pos*
 * @param TYPE_RESSOURCE - *ressourceSol* ChantierSpatialrai correspondant au type de sol
 * @param TYPE_RESSOURCE - *ressourceProduite* ChantierSpatialrai
 */
ChantierSpatial::ChantierSpatial(const Vector2u &pos)
    : Batiment{pos, _texturesChantierSpatials[0]},
      _idChantierSpatial(++_idMaxChantierSpatials),
      _zoomTexture{0, 0, 655, 655}
{
    _nbChantierSpatials++;

    setSpriteTexture(0);
    cerr << "ChantierSpatial(), id : " << _idChantierSpatial << endl;
}

void ChantierSpatial::init() {}

ChantierSpatial::~ChantierSpatial()
{
    _nbChantierSpatials--;
    cerr << "~ChantierSpatial(), id : " << _idChantierSpatial << endl;
}

/*******************************************************/
/*******************************************************/

void ChantierSpatial::chargerMemoireChantierSpatials()
{
    cerr << endl
         << "chargerMemoireChantierSpatials" << endl;
    chargerTextures(cheminFichierTexturesChantierSpatials);
    _offsetTextureX = _tailleTexture / 4;
    _offsetTextureY = _offsetTextureX;
}

void ChantierSpatial::dechargerMemoireChantierSpatials()
{
    cerr << endl
         << "dechargerMemoireChantierSpatials" << endl;
    for (int i = 0; i < NB_CHANTIER_SPATIALS; ++i)
    {
        delete _texturesChantierSpatials[i];
    }
}

/*******************************************************/

/**
 * @brief Charge les textures des différentes ChantierSpatials en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void ChantierSpatial::chargerTextures(string fichierCheminsTexture)
{
    string nomFichierTexture[NB_CHANTIER_SPATIALS];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des ChantierSpatials" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_CHANTIER_SPATIALS; ++k)
        {
            // Chemin de l'image texture d'une ChantierSpatial
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesChantierSpatials[k] = texture;
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

void ChantierSpatial::dessiner(float scaleSprite)
{
    // Décalage animation
    setSpriteTexture(contextGlobal->getCurrentTick());
    _sprite->setTextureRect(_zoomTexture);

    Batiment::dessiner(scaleSprite);
}

/**
 * @brief Zoom la texture de la ChantierSpatial en fonction du niveau et de l'animation
 *
 * @param uint - *tick*
 */
void ChantierSpatial::setSpriteTexture(uint tick)
{
    _zoomTexture.top = _level * _offsetTextureY;
    _zoomTexture.left = tick * _offsetTextureX;

    _sprite->setTextureRect(_zoomTexture);
}

/**
 * @brief Définie la bonne texture en fonction de la ressource craftée.
 * @details ChantierSpatial sans ressource à craft => _textureMines[0]
 * ChantierSpatial Regolite => _textureMines[1] ...
 *
 * @param TYPE_RESOOURCE - *ressCraft*
 */
void ChantierSpatial::setTextureRessourceCraft(TYPE_RESSOURCE ressCraft)
{
    short indice = (short)ressCraft - (short)_premiereRessourceChantierSpatial + 1;

    _sprite->setTexture(*_texturesChantierSpatials[indice]);
}