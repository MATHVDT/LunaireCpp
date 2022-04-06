#ifndef __BATIMENT_HPP__
#define __BATIMENT_HPP__

#include <iostream>
#include <sys/types.h>

#include "Structure.hpp"

class Batiment : public Structure
{
protected:
    uint _idBatiment;
    Structure *_voisinage[6]; // Ne pas delete
    Structure *_sortie; // Ne pas delete

private: // Static
    static uint _nbBatiments;

public: // Static
    static uint getNbBatiments();

public:
    Batiment(Vector2f pos);
    virtual ~Batiment();

    virtual void init();

    virtual void dessiner(float scaleSprite) ;
    virtual void update() ;

    void deconnecterStructure(Structure *structure);

    // Getter
    uint getIdBatiment() const;
    Structure *getSortie() const;

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

#endif