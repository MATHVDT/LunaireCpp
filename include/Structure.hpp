#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include <iostream>
#include <sys/types.h>

class Structure
{
private:
    // Static
private:
    static uint _nbStructures;

public:
    static uint getNbStructures();

public:
    Structure();
    virtual ~Structure();

    virtual void dessiner() = 0;
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Structure::getNbStructures() { return _nbStructures; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif