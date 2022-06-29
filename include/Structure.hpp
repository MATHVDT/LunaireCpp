/**
 * @file Structure.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Structure
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include <iostream>
#include <list>
#include <queue>
#include <sys/types.h>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "EnumTypeRessource.hpp"
#include "direction.hpp"

#include "ContextGlobal.hpp"

class ContextGlobal;

extern ContextGlobal *contextGlobal;

using namespace std;
using namespace sf;

class Structure
{
private:
    uint _idStructure;

protected:
    Vector2u _position; // Position case dans la carte hexagonale (x, y)
    Sprite *_sprite;

    uint _level;

    list<Structure *> _listStructuresConnectees;
    Structure *_sortie;

    uint _tailleStockEntree;
    uint _tailleStockSortie;
    queue<TYPE_RESSOURCE> _stockEntree;
    queue<TYPE_RESSOURCE> _stockSortie;

private: // Static
    static uint _nbStructures;
    static uint _idMaxStructures;

public: // Static
    static uint getNbStructures();
    static uint getIdMaxStructures();

    static void chargerMemoireStructures();
    static void dechargerMemoireStructures();

public:
    Structure();
    Structure(const Vector2u &pos,
              Texture *,
              uint tailleStockEntree,
              uint tailleStockSortie);
    virtual ~Structure();

    virtual void init();

    virtual void dessiner(float scaleSprite) = 0;
    virtual void update();

    // Getter
    uint getIdStructure() const;
    uint getTailleStockEntree() const;
    uint getTailleStockSortie() const;

    const Vector2u &getPositionCarte() const;

    uint getLevel() const;

    virtual bool stockEntreePlein() const;
    uint getNbEntrees() const;
    uint getNbConnexions() const;
    bool getASortie() const;

    list<Structure *> getStructuresConnecteesEntrantes() const;
    list<Structure *> getStructuresConnectees() const;
    Structure *getSortie() const;

    // Setter
    bool setSortie(Structure *structure);
    void setPositionCarte(const Vector2u &pos);
    void setTailleStockEntree(uint newVal);
    void setTailleStockSortie(uint newVal);

    virtual void process() = 0;

    // Gestion des structures connectées
    bool connecterStructure(Structure *s, bool commeSortie = true, bool connexionAutreSens = false);
    bool deconnecterStructure(Structure *s);
    virtual bool updateOrientation() = 0;

    TYPE_RESSOURCE livrerStock();
    virtual void remplirStock();

    virtual bool checkConnexionPossible(Structure *s, bool commeSortie);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Structure::getNbStructures() { return _nbStructures; }
inline uint Structure::getIdMaxStructures() { return _idMaxStructures; }

inline const Vector2u &Structure::getPositionCarte() const { return _position; }

inline void Structure::setPositionCarte(const Vector2u &pos) { _position = pos; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline uint Structure::getIdStructure() const { return _idStructure; }

inline bool Structure::getASortie() const { return _sortie; }

inline uint Structure::getNbConnexions() const { return _listStructuresConnectees.size(); }
inline uint Structure::getNbEntrees() const { return getNbConnexions() - (_sortie != nullptr); }

inline uint Structure::getLevel() const { return _level; }

inline bool Structure::stockEntreePlein() const { return _stockEntree.size() == _tailleStockEntree; }

inline uint Structure::getTailleStockEntree() const { return _tailleStockEntree; }
inline uint Structure::getTailleStockSortie() const { return _tailleStockSortie; }

inline void Structure::setTailleStockEntree(uint newValue) { _tailleStockEntree = newValue; }
inline void Structure::setTailleStockSortie(uint newValue) { _tailleStockSortie = newValue; }

#endif