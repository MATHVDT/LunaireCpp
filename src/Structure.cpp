/**
 * @file Structure.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Pipeline
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#include "Structure.hpp"

uint Structure::_nbStructures = 0;
uint Structure::_idMaxStructures = 0;

Structure::Structure()
    : _idStructure(++_idMaxStructures),
      _position(),
      _sprite{},
      _level{0},
      _listStructuresConnectees{},
      _sortie(nullptr),
      _tailleStockEntree(1),
      _tailleStockSortie(1),
      _stockEntree{}, _stockSortie{}
{
    _nbStructures++;
    // Vector2f posEcran = Carte::carteToPositionEcran(_position);
    // _sprite->setPosition(posEcran);
    // cerr<< "Structure() = default, id : " << _idStructure << endl;
}

Structure::Structure(const Vector2u &pos,
                     Texture *text,
                     uint tailleStockEntree,
                     uint tailleStockSortie)
    : _idStructure(++_idMaxStructures),
      _position(pos),
      _sprite{new Sprite()},
      _level{0},
      _listStructuresConnectees{},
      _sortie(nullptr),
      _tailleStockEntree(tailleStockEntree),
      _tailleStockSortie(tailleStockSortie),
      _stockEntree{}, _stockSortie{}
{
    // cerr<< "Structure(), id : " << _idStructure << endl;
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
    while (!_listStructuresConnectees.empty())
    {
        deconnecterStructure(*_listStructuresConnectees.begin());
    }
    // cerr<< "~Structure(), id : " << _idStructure << endl;
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
    // Batiment::chargerMemoireBatiments();
    // Pipeline::chargerMemoireBatiments();
}

/**
 * @brief Libère la mémoire allouée aux structures
 * (textures ...)
 */
void Structure::dechargerMemoireStructures()
{
    // Pipeline::dechargerMemoireBatiments();
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
    contextGlobal->dessinerFenetre(_sprite);
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
 * @return TYPE_RESSOURCE
 */
TYPE_RESSOURCE Structure::livrerStock()
{
    if (_stockSortie.empty())
    {
        return TYPE_RESSOURCE::Rien;
    }
    else
    { // Récupère la ressource du stock de sortie
        TYPE_RESSOURCE r = _stockSortie.front();
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
    TYPE_RESSOURCE ress;
    // Pour toutes les connexions aux batiments
    for (auto s : _listStructuresConnectees)
    {
        if (s != _sortie) // S'il s'agit d'une entrée
        {
            ress = s->livrerStock();
            // Si une ressource a été récup -> ajout au stock d'entrée
            if (ress != TYPE_RESSOURCE::Rien)
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
 * @brief Check si la connexion entre les 2 Structures, test si c'est la structure que l'on veut connectée qui peut être connectée.
 *
 * @param Structure * - *s*
 * @param bool - *commeSortie*
 *
 * @return true - *Connexion possible*
 * @return false - *Connexion impossible*
 */
bool Structure::checkConnexionPossible(Structure *s, bool commeSortie)
{
    // Verrifier que la struct existe bien
    if (s == nullptr)
        return false;

    // Test sur this
    // Vérifie sortie est libre
    if (commeSortie && _sortie != nullptr)
    { // Ya déjà une structure en sortie
        return false;
    } // Verifie entrée libre
    else if (!commeSortie &&
             this->getNbEntrees() >= this->getTailleStockEntree())
    { // Toutes les entrées prises
        return false;
    }

    // Test sur la structure à connecter
    // Test si ya de la place en entrée sur s
    if (commeSortie &&
        s->getNbEntrees() >= s->getTailleStockEntree())
    { // Ya plus de place en entrée
        cerr << "Plus de place, nb entrée : " << s->getNbEntrees() << " nb max : " << s->getTailleStockEntree() << endl;
        return false;
    } // Test si y a déjà une sortie sur s
    else if (!commeSortie &&
             s->getASortie() == true)
    { // La structure a déjà une sortie
        // cerr<< "Plus de place en sortie pour " << s << endl;
        return false;
    }

    // Verifier que la Structure est bien adajacente
    bool structAdjacente = false;
    for (int dir = DIRECTION::NORD;
         dir <= DIRECTION::NORDEST; ++dir)
    { // Check position adjacente dans dir
        structAdjacente |=
            (positionCaseVoisine(_position, dir) == (Vector2i)s->getPositionCarte());
    }

    // Si la Structure n'est pas adjacent alors false
    if (!structAdjacente)
    {
        // cerr<< "Structu pas adjacente" << endl;
        return false;
    }
    // Check création d'un circuit avec la connexion
    if (!commeSortie && checkConnexionCircuit(s, commeSortie))
    {
        // cerr<< "Crée un circuit" << endl;
        return false;
    }
    return true;
}

/**
 * @brief Connecte une *Structure*, par default la structure sera ajoutée comme une sortie
 *
 * @param Structure * - *s*
 * @param bool - *commeSortie = true*
 * @param bool - *connexionAutreSens = false*
 *
 * @return true - *Si la Structure a été connectée en tant que sortie ou entrée*
 * @return false - *Pas de possible de connecter*
 */
bool Structure::connecterStructure(Structure *s, bool commeSortie, bool connexionAutreSens)
{
    if (s == nullptr)
    {
        // cerr<< "Connexion struct null" << endl;
        return false;
    }

    // Connexion possible :
    // Structure adjacente
    // Sortie ok sur la structure qui doit l'être
    // Nb de connexion ok
    // Pas de circuit crée
    if (!checkConnexionPossible(s, commeSortie))
    {
        if (!connexionAutreSens)
        {
            return false;
        }
    }

    // Test si la structure est déjà connectée
    if (find(_listStructuresConnectees.begin(),
             _listStructuresConnectees.end(),
             s) != _listStructuresConnectees.end())
    {
        // cerr<< "struct deja co" << endl;
        return false;
    }

    // TESTER SI CA NE CREER PAS UNE BOUCLE DANS LE "GRAPHE"
    // EN GROS REMONTER LE CHEMIN COMME SI ON AVAIT CO
    // ET VERIFIER QU'ON RETOMBE PAS SUR L'OBJET THIS

    // Ajoute a la liste des structures connectées
    this->_listStructuresConnectees.push_back(s);

    // Set la sortie
    if (commeSortie && this->setSortie(s))
    { // Ajoute la connexion comme une entrée dans l'autre sens
        s->connecterStructure(this, false, true);
    }
    else
    { // La connexion sera une entrée
      // Ajoute la connexion comme une sortie dans l'autre sens
        s->connecterStructure(this, true, true);
    }
    return true;
}

/**
 * @brief Vérifie que la connexion ne fait pas de circuit.
 *
 * @param Structure * - *s*
 * @param bool - *commeSortie*
 * @return true - *Si la connexion crée un circuit*
 * @return false - *Si la connexion ne crée pas de circuit*
 */
bool Structure::checkConnexionCircuit(Structure *s, bool commeSortie)
{
    // Test que l'ajout ne fasse pas une boucle/circuit
    queue<Structure *> connexe{};
    Structure *tmp;
    // Connecte comm une entrée, le chemin par de la sortie
    if (!commeSortie && _sortie != nullptr)
        connexe.push(_sortie); // Enfile la sortie
    else if (commeSortie && s->getASortie())
        connexe.push(s->getSortie());

    while (!connexe.empty())
    {
        // Récupère le 1er elt pour le traiter
        tmp = connexe.front();
        // cerr<< "elt top : " << tmp << endl;
        connexe.pop();

        // Correspond à la structure
        // que l'on veut connecter
        // à qui l'on veut connecter
        if (tmp == s || tmp == this)
            return true; // Boucle/Circuit

        // On parcours le chemin
        if (tmp->getASortie())
            connexe.push(tmp->getSortie());
        // cerr<< "Boucle et taille : " << connexe.size() << endl;
    }
    return false;
}

/**
 * @brief Defini la *Structure* de sortie de la *Structure*
 *
 * @details Chaque *Structure* ne peut avoir qu'une structure de sortie.
 * @warning La Structure est déjà connectée ou en train d'être connectée
 * @todo A finir ...
 *
 * @param Structure * - *structure*
 *
 * @return true - *Si la structure a bien été définie comme la sortie*
 * @return false - *Si la structure n'a PAS être définie comme la sortie, car il y avait déjà une sortie*
 */
bool Structure::setSortie(Structure *structure)
{
    // Définie la sortie
    if (_sortie == nullptr)
    {
        _sortie = structure;
        return true;
    }
    else
    { // Déjà une sortie
        return false;
    }
}

/*******************************************************/

/**
 * @brief Deconnecte une structure
 *
 * @param Structure - *s*
 * @return true - *Si les structures ont bien été déconnectées correctement*
 * @return false - *S'il y a eu un soucis dans la déconnexion*
 */
bool Structure::deconnecterStructure(Structure *structADeconnectee)
{
    if (structADeconnectee == nullptr)
        return false;

    // Suppression de la structure connectée
    int nbStructConnectee = _listStructuresConnectees.size();

    this->_listStructuresConnectees.remove_if(
        [structADeconnectee](Structure *s)
        {
            if (s == structADeconnectee)
            { // Save struct connectée
                return true;
            }
            else
            {
                return false;
            }
        });
    // Verification si la suppression c'est bien faite
    if (this->_listStructuresConnectees.size() != nbStructConnectee - 1)
        return false; // Erreur

    // Reset sortie si besoin
    if (this->_sortie == structADeconnectee)
        _sortie = nullptr;

    // Suppression dans l'autre sens
    int nbStructConnecteeSave = structADeconnectee->_listStructuresConnectees.size();
    structADeconnectee->_listStructuresConnectees.remove_if(
        [this](Structure *s)
        {
            return (s == this);
        });

    // Verification si la suppression c'est bien faite
    if (structADeconnectee->_listStructuresConnectees.size() != nbStructConnecteeSave - 1)
        return false; // Erreur

    // Reset de la sortie si besoin
    if (structADeconnectee->_sortie == this)
        structADeconnectee->_sortie = nullptr;

    // Deconnexion ok dans les deux sens
    return true;
}

/*******************************************************/

/*******************************************************/

/**
 * @brief Donne une liste des *Structure* en entrée de la *Structure*
 *
 * @return list<Structure *> - *listEntrees*
 */
list<Structure *> Structure::getStructuresConnecteesEntrantes() const
{
    Structure *structSortie = _sortie;

    list<Structure *> listEntrees = _listStructuresConnectees;
    listEntrees.remove_if([structSortie](Structure *s)
                          { return (structSortie == s); });

    return listEntrees;
}

/**
 * @brief Donne une liste des *Structure* en entrée et sortie de la *Structure*
 *
 * @return list<Structure *> - *_listStructuresConnectees*
 */
list<Structure *> Structure::getStructuresConnectees() const
{
    return _listStructuresConnectees;
}

/**
 * @deprecated Nouvelle gestion direction et ajoute structure connectee
 *
 * @brief Donne la  avec le batiment suivant la direction indiquée
 *
 * @param const Vector2i & - *dir*
 * @return connexion_t * - *(nullptr s'il n'y a rien de connecté)*
 */
// connexion_t *Structure::getConnexionDirection(const Vector2i &dir) const
// {
//     int dirInt = directionVecteurToInt(dir);
//     for (auto c : _listStructuresConnectees)
//     {
//         if (c->direction == dir)
//         {
//             return c;
//         }
//     }

//     return nullptr;
// }

/**
 * @deprecated Nouvelle gestion direction et ajoute structure connectee
 *
 * @overload N'a plus trop d'utilité *(enfin je crois)*
 *
 * @param int DIRECTION
 * @return connexion_t *
 */
// connexion_t *Structure::getConnexionDirection(int DIRECTION) const
// {
//     Vector2i dirVect = directionIntToVecteur(DIRECTION);
//     return getConnexionDirection(dirVect);
// }

/**
 * @brief Donne la *Structure* sortante de la *Structure*
 *
 * @return Structure * - *(nullptr s'il n'y a pas de sortie)*
 */
Structure *Structure::getSortie() const
{

    return _sortie;
}

/*******************************************************/
