#include "Batiment.hpp"

uint Batiment::_nbBatiments = 0;
connexion_t ConnexionNull{};

Batiment::Batiment(Vector2f pos) : Structure(pos), _idBatiment(_nbBatiments++), _listConnexions{}, _sortie(false) {}

Batiment::~Batiment()
{
    // Deconnecte tous les structures
    while (!_listConnexions.empty())
    {
        deconnecterStructure(*_listConnexions.begin());
    }
}

/**
 * @brief Defini une structure de sortie sur le batiment
 * @details Chaque batiment ne peut avoir qu'une structure de sortie
 * @warning Suppose que le batiment possède déjà la connexion avec la structure
 * @param Structure * - *structure*
 */
void Batiment::setSortie(Structure *structure)
{
    for (auto c : _listConnexions)
    {
        if (c->structure == structure)
        {
            c->sortie = true;
            _sortie == true;
        }
    }
}
void Batiment::init() {}

void Batiment::dessiner(float scaleSprite) {}

void Batiment::update() {}

/**
 * @brief Déconnecte une structure du batiment
 * @param Structure * - *structure*
 * @warning ne pas utiliser, pas d'accès pour deco autre structure
 */
void Batiment::deconnecterStructure(Structure *structure)
{
    _listConnexions.remove_if([structure](connexion_t *c)
                              { return c->structure == structure; });
}

/**
 * @brief Déconnecte une connexion du batiment
 * @todo deco de l'autre structure
 * @param connexion_t * - *connexion*
 */
void Batiment::deconnecterStructure(connexion_t *c)
{
    _listConnexions.remove(c);
    // deco autre structure
    // delete c;
}

/**
 * @brief Donne une liste des *connexion_t* en entrée sur le Batiment
 *
 * @return list<connexion_t *> - *listEntrees*
 */
list<connexion_t *> Batiment::getConnexionsEntrantes() const
{
    list<connexion_t *> listEntrees = _listConnexions;
    listEntrees.remove_if([](connexion_t *c)
                          { return c->sortie == true; });
    return listEntrees;
}

/**
 * @brief Donne une liste des *connexion_t* en entrée et sortie sur le Batiment
 *
 * @return list<connexion_t *> - *_listConnexions*
 */
list<connexion_t *> Batiment::getConnexions() const
{
    return _listConnexions;
}

/**
 * @brief Donne la connexion avec le batiment suivant la direction indiquée
 *
 * @param const Vector2i & - *dir*
 * @return connexion_t * - *(nullptr s'il n'y a rien de connecté)*
 */
connexion_t *Batiment::getConnexionDirection(const Vector2i &dir) const
{
    int dirInt = directionVecteurToInt(dir);
    for (auto c : _listConnexions)
    {
        if (c->direction == dir)
        {
            return c;
        }
    }

    return nullptr;
}

/**
 * @overload N'a plus trop d'utilité *(enfin je crois)*
 *
 * @param int DIRECTION
 * @return connexion_t *
 */
connexion_t *Batiment::getConnexionDirection(int DIRECTION) const
{
    Vector2i dirVect = directionIntToVecteur(DIRECTION);
    return getConnexionDirection(dirVect);
}

/**
 * @brief Donne la connexion sortante du batiment
 *
 * @return connexion_t * - *(nullptr s'il n'y a pas de sortie)*
 */
connexion_t *Batiment::getConnexionSortie() const
{
    for (auto c : _listConnexions)
    {
        if (c->sortie)
        {
            return c;
        }
    }
    return nullptr;
}

/*******************************************************/

/**
 * @brief Check si la connexion est possible : sur la direction et sur la sortie
 *
 * @param connexion_t - *c*
 * @return true - *Connexion possible*
 * @return false - *Connexion impossible*
 */
bool Batiment::checkConnexionPossible(connexion_t *c)
{
    // Regarde si la direction n'est pas déjà prise
    auto libre = getConnexionDirection(c->direction);
    if (libre != nullptr)
        return false;

    // Regarde s'il y a déjà une sortie sur le batiment
    if (c->sortie && _sortie)
        return false;
    return true;
}

/**
 * @brief Ajoute une *connexion_t* au batiment
 *
 * @param connexion_t * - *c*
 * @return true - *Si la connexion a été ajouté*
 * @return false - *Si la connexion n'a pas pu être ajouté*
 */
bool Batiment::ajouterConnexion(connexion_t *c)
{
    // Check si l'on peut bien ajouter la connexion
    if (!checkConnexionPossible(c))
        return false;

    // Crée un connexion inverse pour l'autre structure
    connexion_t *cInverse = new connexion_t{this, directionOpposee(c->direction), !c->sortie};
    // Connecte et check si l'autre structure peut être connectée
    if (!c->structure->connecte(cInverse))
        return false;

    // Ajoute la connexion au batiment
    _listConnexions.push_back(c);

    // Enregistre la sortie si besoin
    _sortie = _sortie || c->sortie;

    return true;
}

bool Batiment::connecte(connexion_t *c)
{
    if (!checkConnexionPossible(c))
        return false;

    this->_listConnexions.push_back(c);
    // Enregistre la sortie si besoin
    _sortie = _sortie || c->sortie;

    return true;
}
