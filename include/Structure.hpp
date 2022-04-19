#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include <iostream>
#include <sys/types.h>

#include "ContextGlobal.hpp"
#include "enum_ressource.hpp"
#include "connexion_t.hpp"
#include "direction.hpp"

#include "Carte.hpp"

struct connexion_t;
// class Carte;

// Initialisation dans main.cpp
extern ContextGlobal &contextGlobal;

class Structure
{

protected:
    uint _idStructure;
    Vector2u _position; // Position case dans la carte hexagonale
    Sprite *_sprite;

    static uint _nbStructures;
    static uint _idMaxStructures;

public:
    static uint getNbStructures();
    static uint getIdMaxStructures();

public:
    Structure(Vector2u pos, Texture *text);
    virtual ~Structure();

    virtual void init();

    virtual void dessiner(float scaleSprite) = 0;
    virtual void update() = 0;

    // Getter
    uint getIdStructure() const;
    const Vector2u &getPosition() const;

    // Setter
    void setPosition(const Vector2u &pos);

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

inline const Vector2u &Structure::getPosition() const { return _position; }

inline void Structure::setPosition(const Vector2u &pos) { _position = pos; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline uint Structure::getIdStructure() const { return _idStructure; }

#endif