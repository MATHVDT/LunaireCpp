#include "MasterBatiment.hpp"

string cheminFichierMasterBatiment = "ressource/cheminTextures/cheminTexturesMasterBatiment";

uint MasterBatiment::_tailleStockEntree = 6;
uint MasterBatiment::_tailleStockSortie = 0;
Texture *MasterBatiment::_textureMasterBatiment = nullptr;

MasterBatiment::MasterBatiment(const Vector2u &pos)
    : Batiment{pos, _textureMasterBatiment,
               _tailleStockEntree,
               _tailleStockSortie}
{
}

MasterBatiment::~MasterBatiment() {}

void MasterBatiment::init() {}

void MasterBatiment::dessiner(float scaleSprite)
{
    Batiment::dessiner(scaleSprite);
}

void MasterBatiment ::update()
{
    Batiment::update();
}

/**
 * @brief Process les ressources, ie les vend
 *
 */
void MasterBatiment::process()
{
    // Retire le stock (vente de ressource)
    if (!_stockEntree.empty())
    {
        _stockEntree.pop();
    }
}

/**
 * @brief Pas d'update d'orientation pour le MasterBatiment.
 *
 * @return false - *Toujours False*
 */
bool MasterBatiment::updateOrientation()
{
    return false;
}

/**
 * @brief Check si la connexion est possible, pour le MasterBatiment pas de sortie possible.
 *
 * @param Structure * - *s*
 * @param bool - *commeSortie*
 * @return true - *Connexion possible*
 * @return false - *Connexion IMPOSSIBLE*
 */
bool MasterBatiment::checkConnexionPossible(Structure *s, bool commeSortie)
{
    if (commeSortie)
        return false;
    return Batiment::checkConnexionPossible(s, commeSortie);
}

/************************************************************************/
/************************************************************************/

void MasterBatiment::chargerMemoireMasterBatiment()
{
    cerr << endl
         << "chargerMemoireMasterBatiment" << endl;
    chargerTextures(cheminFichierMasterBatiment);
}
void MasterBatiment::dechargerMemoireMasterBatiment()
{
    cerr << endl
         << "dechargerMemoireMasterBatiment" << endl;
    delete _textureMasterBatiment;
}

void MasterBatiment::chargerTextures(string fichierCheminsTexture)
{
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << endl
             << "Chargement de la texture du MasterBatiment" << endl
             << endl;
        // Chemin de l'image texture d'une Pipeline
        monFlux >> cheminTexture;
        cerr << cheminTexture << endl;

        // Create de la nouvelle texture
        texture = new Texture();
        texture->loadFromFile(cheminTexture);

        _textureMasterBatiment = texture;

        // Récupère la taille d'une case texture
        // On suppose que le batiment à exactement le meme format/taille que les autres batiments, taille calée sur tailleReference
        // _tailleTexture = texture->getSize().y;

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/************************************************************************/
/************************************************************************/
