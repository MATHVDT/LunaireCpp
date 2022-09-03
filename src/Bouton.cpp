/**
 * @file Bouton.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Bouton
 *
 * @version 0.1
 * @date 2022-08-31
 *
 * @copyright Copyright (c) 2022
 */
#include "Bouton.hpp"

string cheminFichierTexturesBoutons = "./ressource/cheminTextures/cheminTexturesBoutons.txt";

Texture *Bouton::_texturesBoutons[NB_BOUTONS];
// uint Bouton::_largeurBouton = 0; // Largeur d'1 Bouton
// uint Bouton::_hauteurBouton = 0; // Hauteur d'1 Bouton

/**
 * @brief Construct a new Bouton:: Bouton object
 *
 * @param const Vector2f & - *posBouton*
 * @param BoutonType - *type*
 * @param BoutonState - *state*
 * @param GameEvent - *gameEventAction*
 */
Bouton::Bouton(const Vector2f &posBouton,
               BoutonType type,
               BoutonState state,
               GameEvent gameEventAction)
    : _box{posBouton.x, posBouton.y, 0, 0},
      _sprite{new Sprite()},
      _scale(1.f, 1.f),
      _zoomTexture{0, 0, 0, 0},
      _type(type),
      _state(state),
      _action(gameEventAction)
{

    _sprite->setPosition(posBouton);
    _sprite->setTexture(*_texturesBoutons[_type]);
    Vector2u textureSize = _sprite->getTexture()->getSize();

    setScale();
    setSpriteTexture();

    _box.height = _zoomTexture.height = textureSize.y / NB_STATE_BOUTONS;
    _box.width = _zoomTexture.width = textureSize.x;
    // Ajustage à l'écran
    _box.height *= _scale.x;
    _box.width *= _scale.y;
}

Bouton::~Bouton()
{
}

/**
 * @brief Set the scale d'un bouton pour adapter la texture
 * @details Ici c'est le scale spécifique aux gros boutons choix construction
 */
void Bouton::setScale()
{
    Vector2f dimFenetre = (Vector2f)contextGlobal->getDimensionFenetre();
    Vector2f dimMenu = Vector2f{dimFenetre.x / 3, dimFenetre.y};
    Vector2f dimText = (Vector2f)_sprite->getTexture()->getSize();

    // Pour les boutons de choix de construction
    _scale = Vector2f{0.47f * dimMenu.x / dimText.x, dimMenu.y / dimText.y};
}

/*******************************************************/
/*******************************************************/

void Bouton::chargerMemoireBoutons()
{
    cerr << endl
         << "chargerMemoireBoutons" << endl;
    chargerTextures(cheminFichierTexturesBoutons);

    // _largeurBouton = _texturesBoutons[0]->getSize().x;
    // _hauteurBouton = _texturesBoutons[0]->getSize().y / NB_STATE_BOUTONS;
}

void Bouton::dechargerMemoireBoutons()
{
    cerr << endl
         << "dechargerMemoireBoutons" << endl;
    for (int i = 0; i < NB_BOUTONS; ++i)
    {
        delete _texturesBoutons[i];
    }
}

/**
 * @brief Charge les textures des différentes boutons en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Bouton::chargerTextures(string fichierCheminsTexture)
{
    string nomFichierTexture[NB_BOUTONS];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Boutons" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_BOUTONS; ++k)
        {
            // Chemin de l'image texture d'une mine
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesBoutons[k] = texture;
        }

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/*******************************************************/
/*******************************************************/

void Bouton::dessiner(float scaleSprite)
{
    setSpriteTexture(); // Modif text ici ou alors quand changement
    _sprite->setTextureRect(_zoomTexture);

    _sprite->setScale(_scale);

    contextGlobal->dessinerFenetre(_sprite);
}

void Bouton::setPositionEcran(const Vector2f &newPositionEcran)
{
    _box.left = newPositionEcran.x;
    _box.top = newPositionEcran.y;
    _sprite->setPosition(newPositionEcran);
}

void Bouton::deplacerPositionEcran(const Vector2f &translation)
{
    _box.left += translation.x;
    _box.top += translation.y;
    _sprite->setPosition(_box.left, _box.top);
}