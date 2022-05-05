#include "Structure.hpp"

uint Structure::_nbStructures = 0;
uint Structure::_idMaxStructures = 0;

Structure::Structure()
    : _idStructure(++_idMaxStructures),
      _position(),
      _sprite{},
      _listConnexions{},
      _sortie(false),
      _stockEntree{}, _stockSortie{}
{
    _nbStructures++;
    // Vector2f posEcran = Carte::carteToPositionEcran(_position);
    // _sprite->setPosition(posEcran);
    cerr << "Structure() = default, id : " << _idStructure << endl;
}

Structure::Structure(const Vector2u &pos, Texture *text)
    : _idStructure(++_idMaxStructures),
      _position(pos),
      _sprite{new Sprite()},
      _listConnexions{},
      _sortie(false),
      _stockEntree{}, _stockSortie{}
{
    cerr << "Structure(), id : " << _idStructure << endl;
    _nbStructures++;

    _sprite->setTexture(*text);
    Vector2f posEcran = Carte::carteToPositionEcran(_position);
    _sprite->setPosition(posEcran);
}

Structure::~Structure()
{
    _nbStructures--;
    delete _sprite;
    // Deconnecte tous les structures
    while (!_listConnexions.empty())
    {
        deconnecterStructure(*_listConnexions.begin());
    }
    cerr << "~Structure(), id : " << _idStructure << endl;
}

void Structure::init()
{
}

/*******************************************************/

/**
 * @brief Charge la mémoire allouée aux structures
 * (textures ...)
 */
void Structure::chargerMemoireStructures()
{
    // Structure::chargerMemoireBatiments();
}

/**
 * @brief Libère la mémoire allouée aux structures
 * (textures ...)
 */
void Structure::dechargerMemoireStructures()
{
    // Structure::dechargerMemoireBatiments();
}

/*******************************************************/

/**
 * @brief Dessine le sprite de la structure à la bonne taille
 * @details *ObjetFille::dessiner()* doit calculer le scale pour adapté le sprite, et appelé cette méthode pour dessiner le sprite dans la fenêtre au bonne dimension
 * @param float - *scaleSprite*
 */
void Structure::dessiner(float scaleSprite)
{
    _sprite->setScale(scaleSprite, scaleSprite);
    contextGlobal.dessinerFenetre(_sprite);
}

void Structure::update()
{
    // Récupérer les ressources des entrées
    this->remplirStock();

    // Traiter les ressources
    this->process();

    // Mettre les ressources à la sortie
}

/*******************************************************/

/**
 * @brief Donne la ressource du stock de sortie d'un batiment et la retire du stock de sortie
 *
 * @return Ressource
 */
Ressource Structure::livrerStock()
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
void Structure::remplirStock()
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
            { // Si ya encore de la place
                if (!this->stockEntreePlein())
                {
                    _stockEntree.push(ress);
                }
            }
        }
    }
}
/*******************************************************/

/*******************************************************/

/**
 * @brief Check si la connexion est possible : direction libre et sortie unique *(ne regarde pas si le type de structure peut être connectée)*
 *
 * @param connexion_t - *c*
 * @return true - *Connexion possible*
 * @return false - *Connexion impossible*
 */
bool Structure::checkConnexionPossible(connexion_t *c)
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
bool Structure::ajouterConnexion(connexion_t *c)
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


/**
 * @brief Ajoute une connexion déjà complète
 * 
 * @param connexion_t * - *c* 
 * @return true - *Si la connexion a pu être ajouté*
 * @return false - *Si la connexion n'a pas pu être ajouté*
 */
bool Structure::connecte(connexion_t *c)
{
    if (!checkConnexionPossible(c))
        return false;

    this->_listConnexions.push_back(c);
    // Enregistre la sortie si besoin
    _sortie = _sortie || c->sortie;

    return true;
}

/**
 * @brief Defini une structure de sortie sur le batiment
 * @details Chaque batiment ne peut avoir qu'une structure de sortie
 * @warning Suppose que le batiment possède déjà la connexion avec la structure
 * @param Structure * - *structure*
 */
void Structure::setSortie(Structure *structure)
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
bool Structure::deconnecte(Structure *structure)
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
void Structure::deconnecterStructure(Structure *structure)
{
    _listConnexions.remove_if([structure](connexion_t *c)
                              { return c->structure == structure; });
}

/**
 * @brief Déconnecte une connexion du batiment
 * @details Déconnecte une structure et libère la mémoire associée à la connexion. Appelle également la méthode permettant de deconnecté dans l'autre sens la structure connectée
 * @param connexion_t * - *connexion*
 */
void Structure::deconnecterStructure(connexion_t *c)
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
list<connexion_t *> Structure::getConnexionsEntrantes() const
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
list<connexion_t *> Structure::getConnexions() const
{
    return _listConnexions;
}

/**
 * @brief Donne la connexion avec le batiment suivant la direction indiquée
 *
 * @param const Vector2i & - *dir*
 * @return connexion_t * - *(nullptr s'il n'y a rien de connecté)*
 */
connexion_t *Structure::getConnexionDirection(const Vector2i &dir) const
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
connexion_t *Structure::getConnexionDirection(int DIRECTION) const
{
    Vector2i dirVect = directionIntToVecteur(DIRECTION);
    return getConnexionDirection(dirVect);
}

/**
 * @brief Donne la connexion sortante du batiment
 *
 * @return connexion_t * - *(nullptr s'il n'y a pas de sortie)*
 */
connexion_t *Structure::getConnexionSortie() const
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
