#ifndef __BATIMENT_HPP__
#define __BATIMENT_HPP__

#include <iostream>
#include <sys/types.h>

#include "Structure.hpp"
#include "direction.hpp"

class Batiment : public Structure
{
protected:
    uint _idBatiment;
    Structure *_connexion[6]; // Ne pas delete
    Structure *_sortie;       // Ne pas delete

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
    uint getIdBatiment() const;
    Structure *getSortie() const;
    Structure *getConnexion(const Vector2i &dir) const;
    Structure *getConnexion(int DIRECTION) const;

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
inline uint Batiment::getIdBatiment() const { return _idBatiment; }

inline Structure *Batiment::getSortie() const { return _sortie; }

inline Structure *Batiment::getConnexion(const Vector2i &dir) const 
{
    int dirInt = directionVecteurToInt(dir);
    return Batiment::getConnexion(dirInt);
}
inline Structure *Batiment::getConnexion(int DIRECTION) const
{
    if (DIRECTION >= 0 && DIRECTION < 6)
        return _connexion[DIRECTION];
    else
        return nullptr;
}

#endif