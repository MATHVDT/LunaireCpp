#include "Batiment.hpp"

uint Batiment::_nbBatiments = 0;
connexion_t ConnexionNull{};

Batiment::Batiment(Vector2f pos) : Structure(pos), _idBatiment(_nbBatiments++), _listConnexions{}, _sortie(false) {}

Batiment::~Batiment() {}

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
        if (c.structure == structure)
        {
            c.sortie = true;
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
 */
void Batiment::deconnecterStructure(Structure *structure)
{
    _listConnexions.remove_if([structure](connexion_t c)
                              { return c.structure == structure; });
}
/**
 * @brief Déconnecte une connexion du batiment
 *
 * @param connexion_t - *c*
 */
void Batiment::deconnecterStructure(connexion_t c)
{
    _listConnexions.remove(c);
}

/**
 * @brief Donne une liste des *connexion_t* en entrée sur le Batiment
 *
 * @return list<connexion_t> - *listEntrees*
 */
list<connexion_t> Batiment::getConnexionsEntrantes() const
{
    list<connexion_t> listEntrees = _listConnexions;
    listEntrees.remove_if([](connexion_t c)
                          { return c.sortie == true; });
    return listEntrees;
}

/**
 * @brief Donne une liste des *connexion_t* en entrée et sortie sur le Batiment
 *
 * @return list<connexion_t> - *_listConnexions*
 */
list<connexion_t> Batiment::getConnexions() const
{
    return _listConnexions;
}

/**
 * @brief Donne la connexion avec le batiment suivant la direction indiquée
 *
 * @param const Vector2i & - *dir*
 * @return connexion_t & - *(ConnexionNull s'il n'y a rien de connecté)*
 */
connexion_t &Batiment::getConnexionDirection(const Vector2i &dir) const
{
    int dirInt = directionVecteurToInt(dir);
    for (auto c : _listConnexions)
    {
        if (c.direction == dir)
        {
            cout << &c << endl;
            return c;
        }
    }
    return ConnexionNull;
}

/**
 * @overload N'a plus trop d'utilité *(enfin je crois)*
 *
 * @param int DIRECTION
 * @return connexion_t &
 */
connexion_t &Batiment::getConnexionDirection(int DIRECTION) const
{
    Vector2i dirVect = directionIntToVecteur(DIRECTION);
    return getConnexionDirection(dirVect);
}

/**
 * @brief Donne la connexion sortante du batiment
 *
 * @return connexion_t & - *(ConnexionNull s'il n'y a pas de sortie)*
 */
connexion_t &Batiment::getConnexionSortie() const
{
    for (auto c : _listConnexions)
    {
        if (c.sortie)
        {
            cout << &c << endl;
            return c;
        }
    }
    return ConnexionNull;
}
