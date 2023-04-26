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

TYPE_RESSOURCE Mine::_premiereRessourceMine = TYPE_RESSOURCE::PoussiereRegolite; // Ici minerai

uint Mine::_tailleTexture = 0;
Texture *Mine::_texturesMines[NB_MINES];

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
           TYPE_SOL typeSol)
    : Batiment{pos, _texturesMines[0]},
      _idMine(++_idMaxMines),
      _typeSol(typeSol),
      _zoomTexture{0, 0, 655, 655}
{
    _nbMines++;

    setSpriteTexture(0);
    cerr << "Mine(), id : " << _idMine << endl;

    _stockConnexion[0] = TYPE_RESSOURCE::Rien;
    _stockConnexion[1] = TYPE_RESSOURCE::Rien;
    _stockConnexion[2] = TYPE_RESSOURCE::Rien;
    _stockConnexion[3] = TYPE_RESSOURCE::Rien;
    _stockConnexion[4] = TYPE_RESSOURCE::Rien;
    _stockConnexion[5] = TYPE_RESSOURCE::Rien;

    for (auto r : _stockConnexion)
    {
        // cerr << " - " << ressString[r];
    }
    // cerr << endl;
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
    for (int i = 0; i < NB_MINES; ++i)
    {
        delete _texturesMines[i];
    }
}

/*******************************************************/

/**
 * @brief Charge les textures des différentes mines en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Mine::chargerTextures(string fichierCheminsTexture)
{
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Mines" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_MINES; ++k)
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
/*******************************************************/
/*******************************************************/

void Mine::dessiner(float scaleSprite)
{
    // Décalage animation
    setSpriteTexture(contextGlobal->getCurrentTick());
    _sprite->setTextureRect(_zoomTexture);

    // float scaleMine = contextGlobal->getScaleReference();

    Batiment::dessiner(scaleSprite);
    // _sprite->setScale(scaleSprite,scaleSprite);
    // contextGlobal->dessinerFenetre(_sprite);
}

/*******************************************************/

/**
 * @brief Remplir les stocks d'entrée dans la mine avec
 * les minerais
 */
void Mine::remplirStock()
{
    TYPE_RESSOURCE gisement = typeSolToTypeRessource(_typeSol);
    for (uint dir = DIRECTION::NORD;
         dir <= DIRECTION::NORDEST;
         ++dir)
    {
        if (_connexions[dir].type != TypeConnexion::Output)
        {
            _stockConnexion[dir] = gisement;
        }
        // cerr << "Stock connexion Mine : " << ressString[_stockConnexion[dir]] << endl;
    }
    // Affichage stock
    // cerr << "Remplir mine : ";
    for (auto r : _stockConnexion)
    {
        // cerr << " - " << ressString[r];
    }
    // cerr << endl;
}

/*******************************************************/

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

/**
 * @brief Définie la bonne texture en fonction de la ressource craftée.
 * @details Mine sans ressource à craft => _textureMines[0]
 * Mine Regolite => _textureMines[1] ...
 *
 * @param TYPE_RESOOURCE - *ressCraft*
 */
void Mine::setTextureRessourceCraft(TYPE_RESSOURCE ressCraft)
{
    short indice = (short)ressCraft - (short)_premiereRessourceMine + 1;

    _sprite->setTexture(*_texturesMines[indice]);
    _sprite->setTextureRect(_zoomTexture);
}

/**
 * @brief Check si les connexions sont possibles
 *
 * @param Structure * - *s*
 * @param bool - *commeSortie = true*
 * @return true - *Connexion possible*
 * @return false - *Connexion impossible*
 */
bool Mine::checkConnexionPossible(Structure *s, bool commeSortie)
{
    // DESACTIVE TEMPORAIREMENT POUR LE DEV
    // if (!commeSortie)
    // {
    //     return false; // A garder par la suite
    //     // return Batiment::checkConnexionPossible(s, commeSortie);
    // }
    // else
    // {
    //     return Batiment::checkConnexionPossible(s, commeSortie);
    // }

    return Batiment::checkConnexionPossible(s, commeSortie);
}
