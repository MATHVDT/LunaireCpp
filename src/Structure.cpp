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
      _connexions(),
      _stockConnexion{}
{
    _nbStructures++;
    // Définit les directions des connexionx
    for (int dir = NORD; dir <= NORDEST; ++dir)
    {
        _connexions[dir].structure = nullptr;
        _connexions[dir].direction = (DIRECTION)dir;
        _connexions[dir].type = TypeConnexion::Undefined;
        _stockConnexion[dir] = TYPE_RESSOURCE::Rien;
    }
}

Structure::Structure(const Vector2u &pos,
                     Texture *text)
    : _idStructure(++_idMaxStructures),
      _position(pos),
      _sprite{new Sprite()},
      _level{0},
      _connexions(),
      _stockConnexion{}
{
    // cerr<< "Structure(), id : " << _idStructure << endl;
    _nbStructures++;

    _sprite->setTexture(*text);
    Vector2f posEcran = Carte::carteToPositionEcran(_position);
    _sprite->setPosition(posEcran);

    // Définit les directions des connexionx
    for (int dir = NORD; dir <= NORDEST; ++dir)
    {
        _connexions[dir].structure = nullptr;
        _connexions[dir].direction = (DIRECTION)dir;
        _connexions[dir].type = TypeConnexion::Undefined;
        _stockConnexion[dir] = TYPE_RESSOURCE::Rien;
    }
}

Structure::~Structure()
{
    _nbStructures--;
    delete _sprite;
    // Deconnecte tous les structures
    // Plus besoin vu que c'est un tableau
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
    // this->remplirStock();

    // // Traiter les ressources
    process();
    // cout << "Process structure " << endl;
}

void Structure::process()
{
    // cerr << "Process structure : " << _idStructure << endl;
    remplirStock();
}

/*******************************************************/

/**
 * @brief Donne la ressource du stock qui est sur la connexion de sortie *(ouput)*, ou rien s'il n'y a pas de sortie.
 * @warning N'ai jamais appelé directement, c'est la seulement méthode remplirStock qui l'appelle
 *
 * @return TYPE_RESSOURCE - *issue du stock de sortie*
 */
TYPE_RESSOURCE Structure::livrerStock()
{
    TYPE_RESSOURCE ress = TYPE_RESSOURCE::Rien;
    connexion_t *coSortie = getConnexionSortie();

    if (coSortie == nullptr)
    {
        cerr << "Erreur dans livraison stock" << endl;
    }

    DIRECTION dir = coSortie->direction;
    ress = _stockConnexion[dir];
    cerr << "livrer stock Structure : " << ressString[ress] << endl;
    _stockConnexion[dir] = TYPE_RESSOURCE::Rien;

    return ress;
}

/**
 * @brief Récupère les ressources des stocks de sortie des structures connectées *(une seule ressource/structure)* N'écrase pas la ressource déjà présente dans le stock
 */
void Structure::remplirStock()
{
    TYPE_RESSOURCE ress = TYPE_RESSOURCE::Rien;
    // Pour toutes les connexions aux batiments
    for (uint dir = DIRECTION::NORD;
         dir <= DIRECTION::NORDEST;
         ++dir)
    {
        // S'il s'agit d'une entrée
        if (_connexions[dir].type == TypeConnexion::Input)
        {
            if (_stockConnexion[dir] == TYPE_RESSOURCE::Rien)
            { // Il ya de la place
                ress = _connexions[dir].structure->livrerStock();

                cerr << "Reception de livraison dans remplir stock struct : " << ressString[ress] << endl;

                _stockConnexion[dir] = ress;
            }
        }
    }
}
/*******************************************************/

/*******************************************************/

/**
 * @brief Check si la connexion dans un sens est possible.
 * @details Test :
 * - l'existence d'une sorties this
 * - la strucutre déjà connectée ET
 * - l'adjacence de la structure
 * - les circuits
 *
 * @bug Pb de batiment qui se connecte à lui meme : circuit *(a verifier avec nouvelle gestion)*
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
    {
        cerr << "structure null" << endl;
        return false;
    }
    // Verifie s'il ya de la place en connexion
    if (getNbConnexionsLibres() == 0)
    {
        // cerr << "LA" << endl;
        return false; // Toutes les places prises
    }
    // Test sur this
    // Vérifie sortie est libre
    if (commeSortie && getASortie())
    { // Ya déjà une structure en sortie
        cout << "ICI" << endl;
        return false;
    }

    // Test si la structure est déjà connectée ET
    // Verifier que la Structure est bien adajacente
    DIRECTION dirAdjacence = DIRECTION::NULLDIRECTION;
    for (auto c : _connexions)
    {
        if (c.structure == s)
        {
            cerr << "deja co" << endl;
            return false;
        }
        if (c.type == TypeConnexion::Undefined &&
            positionCaseVoisine(_position, c.direction) == (Vector2i)s->getPositionCarte())
        {
            dirAdjacence = c.direction;
        }
    }

    // Si la Structure n'est pas adjacent alors false
    if (dirAdjacence == DIRECTION::NULLDIRECTION)
    {
        // cerr << "Structu pas adjacente ou type co pas undefined" << endl;
        return false;
    }
    // Check création d'un circuit avec la connexion
    if (!commeSortie && checkConnexionCircuit(s, commeSortie))
    {
        cerr << "Crée un circuit" << endl;
        return false;
    }

    // s->checkConnexionPossible(this, !commeSortie);

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
    { // S'il y a bien structure a connecter
        cerr << "Connexion struct null" << endl;
        return false;
    }

    // Connexion possible :
    // Structure adjacente
    // Sortie ok sur la structure qui doit l'être
    // Nb de connexion ok
    // Pas de circuit crée
    if (!connexionAutreSens &&
        (!checkConnexionPossible(s, commeSortie) ||
         !s->checkConnexionPossible(this, !commeSortie)))
    { // Condition de co pas OK
      // Si c'est l'autre sens
      // Pas grave parce que les conditions
      // ont déjà été vérifiés pour les 2 sens
        // cerr << "Un des deux coté pas checkConnexion possible" << endl;
        return false;
    }

    //  Calcule la directions de la connexion
    DIRECTION dirAdjacence = DIRECTION::NULLDIRECTION;
    for (int dir = DIRECTION::NORD;
         dir <= DIRECTION::NORDEST; ++dir)
    { // Check position adjacente dans dir
        if (positionCaseVoisine(_position, dir) == (Vector2i)s->getPositionCarte())
        {
            dirAdjacence = (DIRECTION)dir;
        }
    }
    // Ajout de la connexion
    _connexions[(int)dirAdjacence].direction = dirAdjacence;
    _connexions[(int)dirAdjacence].structure = s;
    _connexions[(int)dirAdjacence].type = (commeSortie ? TypeConnexion::Output : TypeConnexion::Input);

    if (connexionAutreSens)
    { // Connexion dans l'autre sens des structures
        return true;
    }
    else
    { // Un seul coté connecté
        if (s->connecterStructure(this, !commeSortie, true) == false)
        {
            cerr << "ERREUR DE CONNEXION DANS AUTRE SENS, FAUT DECO" << endl;
            return false;
        }
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
    if (!commeSortie && getASortie())
        connexe.push(getSortie()); // Enfile la sortie
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
 * @brief Definit la *Structure* de sortie de la *Structure* si elle est déjà connecté
 *
 * @details Chaque *Structure* ne peut avoir qu'une structure de sortie.
 * @warning La Structure est déjà connectée ou en train d'être connectée
 * @todo A finir ...
 *
 * @param Structure * - *s*
 *
 * @return true - *Si la structure a bien été définie comme la sortie*
 * @return false - *Si la structure n'a PAS être définie comme la sortie, car il y avait déjà une sortie ou batiment pas connecté*
 */
bool Structure::setSortie(Structure *s)
{
    if (getIsStructureConnected(s))
    {                      // Définie la sortie
        if (!getASortie()) // Pas de sortie
        {
            for (auto &c : _connexions)
            {
                if (c.structure == s)
                {
                    c.type = TypeConnexion::Output;
                    return true;
                }
            }
        }
    }
    return false;
}

/*******************************************************/

/**
 * @brief Deconnecte une structure
 *
 * @param Structure - *s*
 * @return true - *Si LES structureS ont bien été déconnectées correctement*
 * @return false - *S'il y a eu un soucis dans la déconnexion*
 */
bool Structure::deconnecterStructure(Structure *structADeconnectee)
{
    if (structADeconnectee == nullptr)
        return false;

    bool deco = false;
    // Déco dans le sens principale
    for (auto &c : _connexions)
    {
        if (c.structure == structADeconnectee)
        {
            c.structure = nullptr;
            c.direction = DIRECTION::NULLDIRECTION;
            c.type = TypeConnexion::Undefined;
            deco = true;
        }
    }
    //  Déco dans l'autre sens
    for (auto &c : structADeconnectee->_connexions)
    {
        if (c.structure == this)
        {
            c.structure = nullptr;
            c.direction = DIRECTION::NULLDIRECTION;
            c.type = TypeConnexion::Undefined;
            deco = deco && true;
        }
    }
    if (deco == false)
    {
        cerr << "Erreur dans la déconnexion dans un des 2 sens" << endl;
    }
    // Deconnexion ok dans les deux sens
    return deco;
}

/*******************************************************/

/*******************************************************/

/**
 * @brief Donne la *Structure* sortante de la *Structure*
 *
 * @return Structure * - *(nullptr s'il n'y a pas de sortie)*
 */
Structure *Structure::getSortie() const
{
    for (auto c : _connexions)
    {
        if (c.type == TypeConnexion::Output)
            return c.structure;
    }
    return nullptr;
}

/*******************************************************/
