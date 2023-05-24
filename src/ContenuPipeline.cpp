#include "ContenuPipeline.hpp"

uint ContenuPipeline::_capacite = 5; // = 5 (entrée + 3 +sortie)

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
      _sprite(new Sprite{*IconeManager::getTexturesRessource()}),
      _contenu{}
{
    // Remplir le contenu de Vide
    for (int k = 0; k < _capacite; ++k)
    {
        _contenu.push(TYPE_RESSOURCE::Rien);
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

    Vector2f Ventree = (M - ME);
    Vector2f Vsortie = (MS - M);

    // Ventree.x += 2*contextGlobal->getCurrentTick();
    // Ventree.y += 2*contextGlobal->getCurrentTick();

    // Vsortie.x += 2*contextGlobal->getCurrentTick();
    // Vsortie.y += 2*contextGlobal->getCurrentTick();
    float moveRand = 1.;
    float scaleRand = 1.;

    Vector2f posDessin;

    for (int i = (2 * _capacite - 1); i > 0; i -= 2)
    {
        // Récupération de la ressources pour affichage
        r = _contenu.front();
        _contenu.pop();
        _contenu.push(r); // Remise dans le contenu de la ressource

        // cerr << "Ressource float : " << static_cast<float>(r) << endl;
        // cerr << "Ressource int   : " << static_cast<int>(r) << endl;
        // cerr << "Ressource       : " << (int)r << endl;

        // moveRand = (0.95 + (1.05 - 0.95) * (float)((float)rand() / (float)RAND_MAX));

        // Calcul de la position
        if (i < 5) // VEntree
        {
            posDessin.x = ME.x + (float)((i % _capacite) / (float)_capacite) * Ventree.x * moveRand;
            posDessin.y = ME.y + (float)((i % _capacite) / (float)_capacite) * Ventree.y * moveRand;
        }
        else if (i >= 5) // VSortie
        {
            posDessin.x = M.x + (float)((i % _capacite) / (float)_capacite) * Vsortie.x * moveRand;
            posDessin.y = M.y + (float)((i % _capacite) / (float)_capacite) * Vsortie.y * moveRand;
        }

        scaleRand = (0.9 + (1.1 - 0.9) * (float)((float)rand() / (float)RAND_MAX));
        _sprite->setScale(scaleSprite * scaleRand,
                          scaleSprite * scaleRand);

        _sprite->setTextureRect(IconeManager::getZoomTextureRessource(r));
        _sprite->setPosition(posDessin);

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
    queue<TYPE_RESSOURCE> &stockEntree)
{
    TYPE_RESSOURCE r;

    if (!stockEntree.empty())
    {
        r = stockEntree.front();
        stockEntree.pop();
    }
    else
    {
        r = TYPE_RESSOURCE::Rien;
    }

    _contenu.push(r);
}

/**
 * @brief Retire la ressource du conten
 *
 * @param const queue<TYPE_RESSOURCE> & - *stockSortie*
 * @return TYPE_RESSOURCE
 */
TYPE_RESSOURCE ContenuPipeline::livrerStock(queue<TYPE_RESSOURCE> &stockSortie)
{
    TYPE_RESSOURCE r = TYPE_RESSOURCE::Rien;

    // Si la sortie est vide ou remplie de Rien
    if (!stockSortie.empty() &&
            stockSortie.front() == TYPE_RESSOURCE::Rien ||
        stockSortie.empty())
    {
        r = _contenu.front();
        _contenu.pop();
        stockSortie.push(r);
    }

    return r;
}
