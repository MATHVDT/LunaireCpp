#include "ContenuPipeline.hpp"

string cheminFichierTexturesTypeRessource = "ressource/cheminTextures/cheminTexturesTypeRessource.txt";

uint ContenuPipeline::_capacite = 5; // = 5 (entrée + 3 +sortie)

uint ContenuPipeline::_tailleTexture = 0; // = 75
Texture *ContenuPipeline::_texturesTypeRessource = nullptr;
uint ContenuPipeline::_offsetTextureX = 75; // Largeur d'1 texture
uint ContenuPipeline::_offsetTextureY = 75; // Hauteur d'1 texture

/**
 * @brief Construct a new Contenu Pipeline:: Contenu Pipeline object
 *
 */
ContenuPipeline::ContenuPipeline(const Vector2u &pos,
                                 DIRECTION &dirEntree,
                                 DIRECTION &dirSortie)
    : _positionCarte{pos},
      _dirEntree(dirEntree),
      _dirSortie(dirSortie),
      _sprite(new Sprite{*_texturesTypeRessource}),
      _zoomTexture{0, 0, (int)_offsetTextureX, (int)_offsetTextureY},
      _contenu{}
{
    // Remplir le contenu de Vide
    for (int k = 0; k < _capacite; ++k)
    {
        _contenu.push(TYPE_RESSOURCE::Rien);
    }
    _sprite->setOrigin(_tailleTexture / 2, _tailleTexture / 2);
}

/***********************************************************************/
/***********************************************************************/

void ContenuPipeline::chargerMemoireTypeRessource()
{
    // cerr << endl << "chargerMemoireTypeRessource" << endl;
    chargerTextures(cheminFichierTexturesTypeRessource);
    _offsetTextureX = _tailleTexture; // Largeur d'une case
    _offsetTextureY = _tailleTexture; // Largeur d'une case
}

void ContenuPipeline::dechargerMemoireTypeRessource()
{
    // cerr << "dechargerMemoireTypeRessource" << endl;
    delete _texturesTypeRessource;
}

/***********************************************************************/

/**
 * @brief Charge les textures des types de Ressource en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void ContenuPipeline::chargerTextures(string fichierCheminsTexture)
{
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << endl
             << "Chargement de la texture des types de ressources" << endl
             << endl;
        // Chemin de l'image texture d'une Pipeline
        monFlux >> cheminTexture;
        cerr << cheminTexture << endl;

        // Create de la nouvelle texture
        texture = new Texture();
        texture->loadFromFile(cheminTexture);

        _texturesTypeRessource = texture;

        // Récupère la taille d'une case texture
        _tailleTexture = texture->getSize().y;

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/***********************************************************************/
/***********************************************************************/

void ContenuPipeline::dessiner(float scaleSprite)
{
    // Test que le pipeline est bien connecté
    if (_dirEntree == DIRECTION::NULLDIRECTION ||
        _dirSortie == DIRECTION::NULLDIRECTION)
        return;

    TYPE_RESSOURCE r;

    Vector2f posEcran = Carte::carteToPositionEcran(_positionCarte);

    Vector2f VDecalageEcranEntree = getVDecalageEcran(_dirEntree);
    Vector2f VDecalageEcranSortie = getVDecalageEcran(_dirSortie);

    Vector2f M = posEcran + getVDecalageEcran(DIRECTION::NULLDIRECTION);
    Vector2f ME = posEcran + VDecalageEcranEntree;
    Vector2f MS = posEcran + VDecalageEcranSortie;

    Vector2f Ventree = M - ME;
    Vector2f Vsortie = MS - M;

    Vector2f posDessin;

    for (int i = (2 * _capacite - 1); i > 0; i -= 2)
    {
        // Récupération de la ressources pour affichage
        r = _contenu.front();
        _contenu.pop();
        _contenu.push(r); // Remise dans le contenu de la ressource

        _zoomTexture.left = static_cast<int>(r) * _offsetTextureX;
        _zoomTexture.width = _tailleTexture;
        _zoomTexture.height = _tailleTexture;

        // Calcul de la position
        if (i < 5) // VEntree
        {
            posDessin.x = ME.x + (float)((i % _capacite) / (float)_capacite) * Ventree.x;
            posDessin.y = ME.y + (float)((i % _capacite) / (float)_capacite) * Ventree.y;
        }
        else if (i >= 5) // VSortie
        {
            posDessin.x = M.x + (float)((i % _capacite) / (float)_capacite) * Vsortie.x;
            posDessin.y = M.y + (float)((i % _capacite) / (float)_capacite) * Vsortie.y;
        }

        _sprite->setTextureRect(_zoomTexture);
        _sprite->setPosition(posDessin);
        _sprite->setScale(scaleSprite, scaleSprite);
        contextGlobal->dessinerFenetre(_sprite);
    }
}

/***********************************************************************/

/**
 * @brief Retourne le décalage nécessaire sur l'écran en fct d'une direction, pour obtenir le point d'entrée/sortie d'un pipeline
 *
 * @param DIRECTION - *dir*
 * @return Vector2f - *decalage écran*
 */
Vector2f ContenuPipeline::getVDecalageEcran(DIRECTION dir)
{
    Vector2f decalage;
    float tailleCase = contextGlobal->getTailleReference();

    switch (dir)
    {
    case DIRECTION::NULLDIRECTION:
        decalage.x = tailleCase / 2;
        decalage.y = tailleCase / 2;
        break;
    case DIRECTION::NORD:
        decalage.x = tailleCase / 2;
        decalage.y = 0;
        break;

    case DIRECTION::NORDOUEST:
        decalage.x = tailleCase / 8;
        decalage.y = tailleCase / 4;
        break;
    case DIRECTION::SUDOUEST:
        decalage.x = tailleCase / 8;
        decalage.y = 3 * tailleCase / 4;
        break;
    case DIRECTION::SUD:
        decalage.x = tailleCase / 2;
        decalage.y = tailleCase;
        break;
    case DIRECTION::SUDEST:
        decalage.x = 7 * tailleCase / 8;
        decalage.y = 3 * tailleCase / 4;
        break;
    case DIRECTION::NORDEST:
        decalage.x = 7 * tailleCase / 8;
        decalage.y = tailleCase / 4;
        break;
    default:
        decalage.x = 0;
        decalage.y = 0;
        break;
    }

    return decalage;
}
/***********************************************************************/

/**
 * @brief Récupère la ressource dans le stockEntree pour le prendre en compte dans le contenu du Pipeline
 *
 * @param const queue<TYPE_RESSOURCE> & - *stockEntree du Pipeline : Structure*
 */
void ContenuPipeline::remplirStock(
    const queue<TYPE_RESSOURCE> &stockEntree)
{
    TYPE_RESSOURCE r = TYPE_RESSOURCE::Rien;

    if (!stockEntree.empty())
        r = stockEntree.front();
    else
        cout << "stocke entree decrait pas etre vide" << endl;
        
    _contenu.push(r);
}

/**
 * @brief Retire la ressource du conten
 *
 * @param const queue<TYPE_RESSOURCE> & - *stockSorite*
 * @return TYPE_RESSOURCE
 */
TYPE_RESSOURCE ContenuPipeline::livrerStock()
{
    TYPE_RESSOURCE r = _contenu.front();

    _contenu.pop();

    return r;
}
