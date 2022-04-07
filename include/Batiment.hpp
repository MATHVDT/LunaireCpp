#ifndef __BATIMENT_HPP__
#define __BATIMENT_HPP__

#include <iostream>
#include <list>
#include <sys/types.h>

#include "Structure.hpp"
#include "direction.hpp"

struct connexion_t
{
    Structure *structure = nullptr;
    Vector2i direction = NullDirection;
    bool sortie = false;
};

extern connexion_t ConnexionNull;

bool operator==(const connexion_t &cg, const connexion_t &cd);

class Batiment : public Structure
{
protected:
    uint _idBatiment;
    list<connexion_t> _listConnexions;
    bool _sortie;

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
    void deconnecterStructure(connexion_t c);

    // Getter
    uint getNbConnexions() const;
    uint getNbEntrees() const;
    uint getIdBatiment() const;
    list<connexion_t> getConnexionsEntrantes() const;
    connexion_t &getConnexionSortie() const;
    list<connexion_t> getConnexions() const;
    connexion_t &getConnexionDirection(const Vector2i &dir) const;
    connexion_t &getConnexionDirection(int DIRECTION) const;

    // Setter
    void setSortie(Structure *structure);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/
inline bool operator==(const connexion_t &cg, const connexion_t &cd)
{
    return (cg.structure == cd.structure &&
            cg.direction == cd.direction &&
            cg.sortie == cd.sortie);
}

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Batiment::getNbBatiments() { return _nbBatiments; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline uint Batiment::getNbConnexions() const { return _listConnexions.size(); }
inline uint Batiment::getNbEntrees() const { return getNbConnexions() - _sortie; }

inline uint Batiment::getIdBatiment() const { return _idBatiment; }

#endif