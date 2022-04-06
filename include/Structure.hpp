#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include <iostream>
#include <sys/types.h>

#include "ContextGlobal.hpp"


// Initialisation dans main.cpp
extern ContextGlobal &contextGlobal;

class Structure
{
private:
    // Static
protected:
    uint _id;
    Vector2f _position;
    Sprite *_sprite;

    static uint _nbStructures;

public:
    static uint getNbStructures();

public:
    Structure(Vector2f pos);
    virtual ~Structure();

    // virtual void update();
    virtual void dessiner() = 0;

    // Getter
    const Vector2f &getPosition() const;

    // Setter
    void setPosition(const Vector2f &pos);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Structure::getNbStructures() { return _nbStructures; }

inline const Vector2f &Structure::getPosition() const { return _position; }

inline void Structure::setPosition(const Vector2f &pos) { _position = pos; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif