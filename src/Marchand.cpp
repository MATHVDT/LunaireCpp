#include "Marchand.hpp"

string cheminFichierMarchand = "ressource/cheminTextures/cheminTexturesMarchand";

Texture *Marchand::_textureMarchand = nullptr;

Marchand::Marchand(const Vector2u &pos)
    : Batiment{pos, _textureMarchand}
{
}

Marchand::~Marchand() {}

void Marchand::init() {}

void Marchand::dessiner(float scaleSprite)
{
    Batiment::dessiner(scaleSprite);
}

void Marchand ::update()
{
    Batiment::update();
}

/**
 * @brief Process les ressources, ie les vend
 *
 */
void Marchand::process()
{
    // cout << "Process Marchand : " << endl;
    afficherStock();

    Batiment::process();

    TYPE_RESSOURCE r;
    for (uint dir = DIRECTION::NORD;
         dir <= DIRECTION::NORDEST;
         ++dir)
    {
        r = _stockConnexion[dir];
        if (r != TYPE_RESSOURCE::Rien)
            cout << "!!!!!!!!!! VENTE DE : " << ressString[r] << "!!!!!!!!!!!" << endl
                 << endl<< endl;
    }
}

/**
 * @brief Pas d'update d'orientation pour le Marchand.
 *
 * @return false - *Toujours False*
 */
bool Marchand::updateOrientation()
{
    return false;
}

/**
 * @brief Check si la connexion est possible, pour le Marchand pas de sortie possible.
 *
 * @param Structure * - *s*
 * @param bool - *commeSortie*
 * @return true - *Connexion possible*
 * @return false - *Connexion IMPOSSIBLE*
 */
bool Marchand::checkConnexionPossible(Structure *s, bool commeSortie)
{
    if (commeSortie)
    {
        return false;
    }
    return Batiment::checkConnexionPossible(s, commeSortie);
}

/*******************************************************/
/*******************************************************/
void Marchand::chargerMemoireMarchand()
{
    cerr << endl
         << "chargerMemoireMarchand" << endl;
    chargerTextures(cheminFichierMarchand);
}

void Marchand::dechargerMemoireMarchand()
{
    cerr << endl
         << "dechargerMemoireMarchand" << endl;
    delete _textureMarchand;
}

/*******************************************************/

void Marchand::chargerTextures(string fichierCheminsTexture)
{
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << endl
             << "Chargement de la texture du Marchand" << endl
             << endl;
        // Chemin de l'image texture d'une Pipeline
        monFlux >> cheminTexture;
        cerr << cheminTexture << endl;

        // Create de la nouvelle texture
        texture = new Texture();
        texture->loadFromFile(cheminTexture);

        _textureMarchand = texture;

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
/*******************************************************/
/*******************************************************/
