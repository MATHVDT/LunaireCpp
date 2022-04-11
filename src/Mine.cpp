#include "Mine.hpp"

uint Mine::_nbMines = 0;
uint Mine::_idMaxMines = 0;

uint Mine::_levelMax = 3;
uint _nbAnim = 4;

Texture *Mine::_texturesMine[NB_RESSOURCES];

// uint Mine::_offsetTextureX = contextGlobal.getTailleReference();
// uint Mine::_offsetTextureY = contextGlobal.getTailleReference();

uint Mine::_offsetTextureX = 100;
uint Mine::_offsetTextureY = 100;

Mine::Mine(Vector2f pos, Ressource type) : Batiment{pos}, _id(++_idMaxMines), _typeRessource(type), _level(0), _zoomTexture(Vector2i(0, 0), Vector2i(_offsetTextureX, _offsetTextureY))
{
    // _sprite->setTexture(*_texturesMine[static_cast<int>(_typeRessource)]);
    _nbMines++;
}

Mine::~Mine()
{
    _nbMines--;
}

void Mine::initMines()
{
    _offsetTextureX = contextGlobal.getTailleReference();
    _offsetTextureY = contextGlobal.getTailleReference();
}

void Mine::init()
{
}

void Mine::dessiner(float scaleSprite)
{
    // Décalage animation

    Batiment::dessiner(scaleSprite);
}

void Mine::update() {}

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
        // Récupération des chemins
        for (int k = 0; k < NB_RESSOURCES; ++k)
        {
            // Chemin de l'image texture d'une mine
            monFlux >> cheminTexture;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesMine[k] = texture;
        }
        // _tailleTexture = texture->getSize().y;
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
}
