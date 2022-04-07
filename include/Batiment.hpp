#ifndef __BATIMENT_HPP__
#define __BATIMENT_HPP__

#include <iostream>
#include <list>
#include <sys/types.h>

#include "Structure.hpp"
#include "direction.hpp"

struct connexion
{
    Structure *structure;
    Vector2i direction = NullDirection;
    bool sortie = false;
};

class Batiment : public Structure
{
protected:
    uint _idBatiment;
    Structure *_connexion[6]; // Ne pas delete
    Structure *_sortie;       // Ne pas delete
    uint _nbConnexions;
    list<connexion> _listConnexions;

private: // Static
    static uint _nbBatiments;

public: // Static
    static uint getNbBatiments();

public:
    Batiment(Vector2f pos);
    virtual ~Batiment();

    virtual void init();

    virtual void dessiner(float scaleSprite);
    virtual void update();

    void deconnecterStructure(Structure *structure);

    // Getter
    uint getNbConnexions() const;
    uint getNbEntrees() const;
    uint getIdBatiment() const;
    Structure *getSortie() const;
    list<Structure *> getEntrees() const;
    list<Structure *> getConnexionDirection() const;
    Structure *getConnexionDirection(const Vector2i &dir) const;
    Structure *getConnexionDirection(int DIRECTION) const;

    // Setter
    void setSortie(Structure *structure);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Batiment::getNbBatiments() { return _nbBatiments; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline uint Batiment::getNbConnexions() const { return _nbConnexions; }
inline uint Batiment::getNbEntrees() const { return _nbConnexions - (_sortie != nullptr); }

inline uint Batiment::getIdBatiment() const { return _idBatiment; }

inline Structure *Batiment::getSortie() const { return _sortie; }

inline Structure *Batiment::getConnexionDirection(const Vector2i &dir) const
{
    int dirInt = directionVecteurToInt(dir);
    return Batiment::getConnexionDirection(dirInt);
}
inline Structure *Batiment::getConnexionDirection(int DIRECTION) const
{
    if (DIRECTION >= 0 && DIRECTION < 6)
        return _connexion[DIRECTION];
    else
        return nullptr;
}

#endif