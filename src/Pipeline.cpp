/**
 * @file Pipeline.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Pipeline
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "Pipeline.hpp"

// A deplacer dans un hpp qui regroupe tous les chemins
string cheminFichierTexturesPipelines = "ressource/cheminTexturesPipelines.txt";

uint Pipeline::_nbPipelines = 0;
uint Pipeline::_idMaxPipelines = 0;

const uint Pipeline::_tailleStockEntree = 1;
const uint Pipeline::_tailleStockSortie = 1;

uint Pipeline::_levelMax = 3;
//  uint Pipeline:: _nbAnim;   // = 1

uint Pipeline::_tailleTexture = 0; // 655

// 3 Textures : Pas connecté | droit | angle
Texture *Pipeline::_texturesPipelines[NB_TEXTURE];
uint Pipeline::_offsetTextureX = 655; // Largeur d'1 texture
uint Pipeline::_offsetTextureY = 655; // Hauteur d'1 texture

/**
 * @brief Construct a new Pipeline:: Pipeline object
 *
 * @param Vector2u & - *pos*
 */
Pipeline::Pipeline(const Vector2u &pos)
    : Structure{pos, _texturesPipelines[NON_CONNECTE],
                _tailleStockEntree, _tailleStockSortie},
      _idPipeline(++_idMaxPipelines),
      _zoomTexture{0, 0,
                   (int)_offsetTextureX,
                   (int)_offsetTextureY},
      _orientation{NULLDIRECTION, NULLDIRECTION,
                   NON_CONNECTE, A_A}
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
    // cerr << endl << "chargerMemoirePipelines" << endl;
    chargerTextures(cheminFichierTexturesPipelines);
    _offsetTextureX = _tailleTexture; // Largeur d'une case
    _offsetTextureY = _tailleTexture; // Largeur d'une case
}

void Pipeline::dechargerMemoirePipelines()
{
    cerr << endl
         << "dechargerMemoirePipelines" << endl;
    for (int i = 0; i < NB_TEXTURE; ++i)
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
    cout << "nb texture enum :" << NB_TEXTURE << endl;
    string nomFichierTexture[NB_TEXTURE];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Pipelines" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_TEXTURE; ++k)
        {
            // Chemin de l'image texture d'une Pipeline
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesPipelines[k] = texture;
        }
        // Récupère la taille d'une case texture
        _tailleTexture = texture->getSize().y / 3;

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

void Pipeline::dessiner(float scaleSprite)
{
    // cerr << "type : " << _orientation.type << endl;
    // cerr << "variant : " << _orientation.variant << endl;
    setSpriteTexture(0);
    Structure::dessiner(scaleSprite);
}

void Pipeline::update() {}

void Pipeline::process() {}

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

    // Changement de Type de Pipeline
    _sprite->setTexture(*_texturesPipelines[_orientation.type]);
    // Changement de Variant de Pipeline
    _zoomTexture.left = _orientation.variant * _offsetTextureX;

    _sprite->setTextureRect(_zoomTexture);

    // cerr << "type : " << _orientation.type << endl;
    // cerr << "variant : " << _orientation.variant << endl;
}

/*******************************************************/
/*******************************************************/

/**
 * @brief Check si la connexion entre le Pipeline et une autre strucutre est possible (nb de connexion)
 *
 * @details Dans la méthode override, on regarde si la structrures peut avoir une connexion suplémentaire (sortie ou entrée). Puis dans la méthode Structure::checkConnexionPossible, on regarde si c'est la structure que l'on veut ajouter qui peut accepter une connexion supplémentaire (entrée ou sortie).
 *
 * @param Structure * - *s*
 * @param bool - *commeSortie*
 *
 * @return true - *Connexion possible*
 * @return false - *Connexion impossible*
 */
bool Pipeline::checkConnexionPossible(Structure *s, bool commeSortie)
{
    // Vérifie sortie est libre
    if (commeSortie && _sortie != nullptr)
    { // Ya déjà une structure en sortie
        cout << "ICI" << endl;
        return false;
    } // Verifie entrée libre
    else if (!commeSortie &&
             this->getNbEntrees() >= this->getTailleStockEntree())
    { // Toutes les entrées prises
        cout << "LA" << endl;
        return false;
    }

    return Structure::checkConnexionPossible(s, commeSortie);
}

/*******************************************************/

/**
 * @brief Calcule l'orientation de Pipeline en fct des connexions dessus
 *
 */
bool Pipeline::updateOrientation()
{
    Vector2i posEntree = Vector2i{-1, -1};
    Vector2i posSortie = Vector2i{-1, -1};

    if (this->getNbEntrees() >= 1)
    {
        posEntree = (Vector2i)(*getStructuresConnecteesEntrantes().begin())->getPositionCarte();
    }

    if (_sortie != nullptr)
        posSortie = (Vector2i)_sortie->getPositionCarte();

    DIRECTION dirEntree = positionOrigineDestToDirection((Vector2i)this->getPositionCarte(), posEntree);
    DIRECTION dirSortie = positionOrigineDestToDirection((Vector2i)this->getPositionCarte(), posSortie);

    _orientation.dirEntree = dirEntree;
    _orientation.dirSortie = dirSortie;

    return calculOrientation(dirEntree, dirSortie);
}
