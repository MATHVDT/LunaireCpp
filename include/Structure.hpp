#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include <iostream>
#include <sys/types.h>

#include "ContextGlobal.hpp"
// #include "connexion_t.hpp"

struct connexion_t;

// Initialisation dans main.cpp
extern ContextGlobal &contextGlobal;

class Structure
{
private:
    // Static
protected:
    uint _idStructure;
    Vector2f _position;
    Sprite *_sprite;

    static uint _nbStructures;

public:
    static uint getNbStructures();

public:
    Structure(Vector2f pos);
    virtual ~Structure();

    virtual void init();

    virtual void dessiner(float scaleSprite) = 0;
    virtual void update() = 0;

    // Getter
    uint getIdStructure() const;
    const Vector2f &getPosition() const;

    // Setter
    void setPosition(const Vector2f &pos);

    virtual bool connecte(connexion_t *) =0;
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
inline uint Structure::getIdStructure() const { return _idStructure; }

#endif