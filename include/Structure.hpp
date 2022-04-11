#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include <iostream>
#include <sys/types.h>

#include "ContextGlobal.hpp"
#include "enum_ressource.hpp"
#include "connexion_t.hpp"
#include "direction.hpp"

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
    static uint _idMaxStructures;

public:
    static uint getNbStructures();
    static uint getIdMaxStructures();

public:
    Structure(Vector2f pos, Texture *text);
    virtual ~Structure();

    virtual void init();

    virtual void dessiner(float scaleSprite) = 0;
    virtual void update() = 0;

    // Getter
    uint getIdStructure() const;
    const Vector2f &getPosition() const;

    // Setter
    void setPosition(const Vector2f &pos);

    virtual bool connecte(connexion_t *) = 0;
    virtual bool deconnecte(Structure *) = 0;

    virtual Ressource livrerStock() = 0;
    virtual void remplirStock() = 0;
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Structure::getNbStructures() { return _nbStructures; }
inline uint Structure::getIdMaxStructures() { return _idMaxStructures; }

inline const Vector2f &Structure::getPosition() const { return _position; }

inline void Structure::setPosition(const Vector2f &pos) { _position = pos; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline uint Structure::getIdStructure() const { return _idStructure; }

#endif