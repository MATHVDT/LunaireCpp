#ifndef __STRUCTURE_HPP__
#define __STRUCTURE_HPP__

#include <iostream>
#include <list>
#include <queue>
#include <sys/types.h>

#include "ContextGlobal.hpp"
#include "enum_ressource.hpp"
#include "connexion_t.hpp"
#include "direction.hpp"
#include "connexion_t.hpp"

#include "Carte.hpp"

// Initialisation dans main.cpp
extern ContextGlobal &contextGlobal;

class Structure
{
private:
    uint _idStructure;

protected:
    Vector2u _position; // Position case dans la carte hexagonale
    Sprite *_sprite;

    list<connexion_t *> _listConnexions;
    bool _sortie;

    uint _tailleStockEntree;
    uint _tailleStockSortie;
    queue<Ressource> _stockEntree;
    queue<Ressource> _stockSortie;

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

    const Vector2u &getPosition() const;

    virtual bool stockEntreePlein() const;
    uint getNbEntrees() const;
    uint getNbConnexions() const;
    bool getASortie() const;

    list<connexion_t *> getConnexionsEntrantes() const;
    list<connexion_t *> getConnexions() const;
    connexion_t *getConnexionSortie() const;
    connexion_t *getConnexionDirection(const Vector2i &dir) const;
    connexion_t *getConnexionDirection(int DIRECTION) const;

    // Setter
    void setSortie(Structure *structure);
    void setPosition(const Vector2u &pos);
    void setTailleStockEntree(uint newVal);
    void setTailleStockSortie(uint newVal);

    virtual void process() = 0;

    // Gestion connextion_t
    void deconnecterStructure(Structure *structure);
    void deconnecterStructure(connexion_t *c);

    bool ajouterConnexion(connexion_t *c);

    bool connecte(connexion_t *c);
    bool deconnecte(Structure *c);

    Ressource livrerStock();
    virtual void remplirStock();

    virtual bool checkConnexionPossible(connexion_t *c);
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

inline bool Structure::getASortie() const { return _sortie; }

inline uint Structure::getNbConnexions() const { return _listConnexions.size(); }
inline uint Structure::getNbEntrees() const { return getNbConnexions() - _sortie; }

inline bool Structure::stockEntreePlein() const { return _stockEntree.size() == _tailleStockEntree; }

inline uint Structure::getTailleStockEntree() const { return _tailleStockEntree; }
inline uint Structure::getTailleStockSortie() const { return _tailleStockSortie; }

inline void Structure::setTailleStockEntree(uint newValue) { _tailleStockEntree = newValue; }
inline void Structure::setTailleStockSortie(uint newValue) { _tailleStockSortie = newValue; }

#endif