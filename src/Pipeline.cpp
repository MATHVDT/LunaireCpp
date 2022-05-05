#include "Pipeline.hpp"

string cheminFichierTexturesPipelines = "ressources/";

uint Pipeline::_nbPipelines = 0;
uint Pipeline::_idMaxPipelines = 0;

const uint Pipeline::_tailleStockEntree = 1;
const uint Pipeline::_tailleStockSortie = 1;

uint Pipeline::_levelMax = 3;
//  uint Pipeline:: _nbAnim;   // = 1

uint Pipeline::_tailleTexture = 0; // 655

// 3 Textures : Pas connecté | droit | angle
Texture *Pipeline::_texturesPipelines[3];
uint Pipeline::_offsetTextureY = 655; // Hauteur d'1 texture

/**
 * @brief Construct a new Pipeline:: Pipeline object
 *
 * @param Vector2u & - *pos*
 */
Pipeline::Pipeline(const Vector2u &pos, Texture *)
    : Structure{pos, _texturesPipelines[0],
                _tailleStockEntree, _tailleStockSortie},
      _idPipeline(++_idMaxPipelines),
      _zoomTexture{0, 0,
                   (int)_offsetTextureY,
                   (int)_offsetTextureY}
{
    ++_nbPipelines;
}

/**
 * @brief Destroy the Pipeline:: Pipeline object
 */
Pipeline::~Pipeline() { --_nbPipelines; }

/*******************************************************/
/*******************************************************/
/*******************************************************/

void Pipeline::chargerMemoirePipelines()
{
    cerr << endl
         << "chargerMemoirePipelines" << endl;
    chargerTextures(cheminFichierTexturesPipelines);
    _offsetTextureY = _tailleTexture; // Largeur d'une case
}

void Pipeline::dechargerMemoirePipelines()
{
    cerr << endl
         << "dechargerMemoirePipelines" << endl;
    for (int i = 0; i < 3; ++i)
    {
        delete _texturesPipelines[i];
    }
}

/*******************************************************/

/**
 * @brief Charge les textures des différentes Pipeline en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Pipeline::chargerTextures(string fichierCheminsTexture)
{
    string nomFichierTexture[3];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Pipelines" << endl;
        // Récupération des chemins
        for (int k = 0; k < 3; ++k)
        {
            // Chemin de l'image texture d'une Pipeline
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesPipelines[k] = texture;
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

void Pipeline::init() {}

void Pipeline::dessiner(float scaleSprite) {}

void Pipeline::update() {}

/*******************************************************/
/*******************************************************/

/**
 * @brief Zoom et rotate la texture du pipeline en fonction du niveau et de la position par rapport aux extremités
 *
 * @param uint - *tick*
 */
void Pipeline::setSpriteTexture(uint tick)
{

    _zoomTexture.top = _level * _offsetTextureY;

    _sprite->setTextureRect(_zoomTexture);

    // cerr << "zoomTexture : ";
    // cerr << _zoomTexture.top << ";" << _zoomTexture.left;
    // cerr << " | " << _zoomTexture.width << ":" << _zoomTexture.height << endl;
}
