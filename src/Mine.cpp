/**
 * @file Mine.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Mine
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "Mine.hpp"

string cheminFichierTexturesMines = "ressource/cheminTextures/cheminTexturesMines.txt";

uint Mine::_nbMines = 0;
uint Mine::_idMaxMines = 0;

uint Mine::_levelMax = 3;
uint _nbAnim = 4;

uint Mine::_tailleTexture = 0;
Texture *Mine::_texturesMines[NB_RESSOURCES];

uint Mine::_offsetTextureX = 100;
uint Mine::_offsetTextureY = 100;

/**
 * @brief Construct a new Mine:: Mine object
 *
 * @param const Vector2u & - *pos*
 * @param TYPE_RESSOURCE - *ressourceSol* Minerai correspondant au type de sol
 * @param TYPE_RESSOURCE - *ressourceProduite* Minerai
 */
Mine::Mine(const Vector2u &pos,
           TYPE_SOL typeSol,
           TYPE_RESSOURCE ressourceProduite)
    : Batiment{pos, _texturesMines[static_cast<int>(ressourceProduite)]},
      _idMine(++_idMaxMines),
      _typeSol(typeSol),
      _typeRessourceProduite(ressourceProduite),
      _zoomTexture{0, 0, 655, 655}
{
    _nbMines++;

    setSpriteTexture(0);
    cerr << "Mine(), id : " << _idMine << endl;
}

void Mine::init() {}

Mine::~Mine()
{
    _nbMines--;
    cerr << "~Mine(), id : " << _idMine << endl;
}

/*******************************************************/
/*******************************************************/

void Mine::chargerMemoireMines()
{
    cerr << endl
         << "chargerMemoireMines" << endl;
    chargerTextures(cheminFichierTexturesMines);
    _offsetTextureX = _tailleTexture / 4;
    _offsetTextureY = _offsetTextureX;
}

void Mine::dechargerMemoireMines()
{
    cerr << endl
         << "dechargerMemoireMines" << endl;
    for (int i = 0; i < NB_RESSOURCES; ++i)
    {
        delete _texturesMines[i];
    }
}

/*******************************************************/

void Mine::dessiner(float scaleSprite)
{
    // Décalage animation
    setSpriteTexture(0);
    _sprite->setTextureRect(_zoomTexture);

    // float scaleMine = contextGlobal->getScaleReference();

    Batiment::dessiner(scaleSprite);
    // _sprite->setScale(scaleSprite,scaleSprite);
    // contextGlobal->dessinerFenetre(_sprite);
}

/*******************************************************/

void Mine::update()
{
    Batiment::update();
    setSpriteTexture(0);
}

/**
 * @brief Remplir les stocks d'entrée dans la mine avec
 * les minerais
 */
void Mine::remplirStock()
{ // Verification s'il c'est la bonne ressouce
    if (_typeRessourceProduite == typeSolToTypeRessource(_typeSol))
    { // Remplissage tant que ya de la place
        while (!stockEntreePlein())
        {
            _stockEntree.push(_typeRessourceProduite);
        }
    }
}

void Mine::process() {}

/*******************************************************/

/**
 * @brief Charge les textures des différentes mines en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Mine::chargerTextures(string fichierCheminsTexture)
{
    string nomFichierTexture[NB_RESSOURCES];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Mines" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_RESSOURCES; ++k)
        {
            // Chemin de l'image texture d'une mine
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesMines[k] = texture;
        }
        _tailleTexture = texture->getSize().x;

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/**
 * @brief Zoom la texture de la mine en fonction du niveau et de l'animation
 *
 * @param uint - *tick*
 */
void Mine::setSpriteTexture(uint tick)
{
    _zoomTexture.top = _level * _offsetTextureY;
    _zoomTexture.left = tick * _offsetTextureX;

    _sprite->setTextureRect(_zoomTexture);

    // cerr << "zoomTexture : ";
    // cerr << _zoomTexture.top << ";" << _zoomTexture.left;
    // cerr << " | " << _zoomTexture.width << ":" << _zoomTexture.height << endl;
}
