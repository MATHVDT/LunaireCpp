#include "Batiment.hpp"

uint Batiment::_nbBatiments = 0;
uint Batiment::_idMaxBatiments = 0;
const uint Batiment::_tailleStockEntree = 6;
const uint Batiment::_tailleStockSortie = 1;

connexion_t ConnexionNull{}; // Inutile je crois

/**
 * @brief Construct a new Batiment:: Batiment object
 * 
 * @param Vector2f - *pos* 
 * @param Texture* - *texture* 
 */
Batiment::Batiment(Vector2u pos, Texture* texture) : Structure(pos, texture), _idBatiment(++_idMaxBatiments), _listConnexions{}, _sortie(false) { _nbBatiments++; }


Batiment::~Batiment()
{
    _nbBatiments--;
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

void Batiment::dessiner(float scaleSprite) {

    Structure::dessiner(scaleSprite);
}

void Batiment::update() {}

/*******************************************************/

/**
 * @brief Deconnecte une structure, sans chercher à deconnecter la structure liée
 *
 * @details Est appelée lorqu'il y a une déconnexion de structure, une fois la connexion enlevé, cette méthode permet d'enlever l'autre *connexion Inverse* sur la structure liée. Libère la mémoire associée à la connexion inverse
 *
 * @param Structure - *structure*
 * @return true - *Si la structure a été déconnectée*
 * @return false - *Si la struture n'a pas été déconnectée"
 */
bool Batiment::deconnecte(Structure *structure)
{
    connexion_t *cSave = nullptr;
    _listConnexions.remove_if(
        [&cSave, structure](connexion_t *c)
        {
            cSave = c;
            return c->structure == structure;
        });

    if (cSave->structure == structure)
        delete cSave;
    else
        return false;
    return true;
}

/*******************************************************/

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
 * @details Déconnecte une structure et libère la mémoire associée à la connexion. Appelle également la méthode permettant de deconnecté dans l'autre sens la structure connectée
 * @param connexion_t * - *connexion*
 */
void Batiment::deconnecterStructure(connexion_t *c)
{
    _listConnexions.remove(c);
    // Déconnecter l'autre structure, connexion inverse
    c->structure->deconnecte(this);
    delete c;
}

/*******************************************************/

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
 * @brief Check si la connexion est possible : direction libre et sortie unique
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

/*******************************************************/

/**
 * @brief Donne la ressource du stock de sortie d'un batiment et la retire du stock de sortie
 *
 * @return Ressource
 */
Ressource Batiment::livrerStock()
{
    if (_stockSortie.empty())
    {
        return Ressource::Rien;
    }
    else
    { // Récupère la ressource du stock de sortie
        Ressource r = _stockSortie.front();
        _stockSortie.pop(); // Enleve du stock
        return r;
    }
}

/**
 * @brief Récupère les ressources des stocks de sortie des structures connectées *(une seule ressource/structure)*
 *
 */
void Batiment::remplirStock()
{
    Ressource ress;
    // Pour toutes les connexions aux batiments
    for (auto c : _listConnexions)
    {
        if (!c->sortie) // S'il s'agit d'une entrée
        {
            ress = c->structure->livrerStock();
            // Si une ressource a été récup -> ajout au stock d'entrée
            if (ress != Ressource::Rien)
                _stockEntree.push(ress);
        }
    }
}

/*******************************************************/
