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
#include <vector>
#include <sys/types.h>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "EnumTypeRessource.hpp"
#include "EnumTypeStructure.hpp"
#include "direction.hpp"
#include "connexion_t.hpp"

#include "ContextGlobal.hpp"

class ContextGlobal;
class Batiment;

extern ContextGlobal *contextGlobal;
// extern void Batiment::chargerMemoireBatiments();

using namespace std;
using namespace sf;

const uint NB_CONNEXIONS = 6;

class Structure
{
private:
    uint _idStructure;

protected:
    Vector2u _position; // Position case dans la carte hexagonale (x, y)
    Sprite *_sprite;

    uint _level;

    connexion_t _connexions[NB_CONNEXIONS];

    // uint _tailleStockEntree;
    // uint _tailleStockSortie;
    // queue<TYPE_RESSOURCE> _stockEntree;
    // queue<TYPE_RESSOURCE> _stockSortie;

    TYPE_RESSOURCE _stockConnexion[NB_CONNEXIONS];

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
              Texture *);
    virtual ~Structure();

    // Virtual
    virtual void init();

    virtual void dessiner(float scaleSprite) = 0;
    virtual void update();
    virtual void process() = 0;

    virtual void remplirStock();
    virtual TYPE_RESSOURCE livrerStock();
    virtual list<TYPE_RESSOURCE> *getListCraftPossible();

    // Gestion des structures connectées
    virtual bool connecterStructure(Structure *s, bool commeSortie = true, bool connexionAutreSens = false);
    virtual bool deconnecterStructure(Structure *s);

    virtual bool checkConnexionPossible(Structure *s, bool commeSortie);
    virtual bool updateOrientation() = 0;

    // Getter
    uint getIdStructure() const;
    uint getTailleStockEntree() const;
    uint getTailleStockSortie() const;

    const Vector2u &getPositionCarte() const;

    uint getLevel() const;

    uint getNbEntrees() const;
    uint getNbConnexionsOccupees() const;
    uint getNbConnexionsLibres() const;
    bool getASortie() const;

    connexion_t *getConnexions();
    Structure *getSortie() const;
    bool getIsStructureConnected(Structure *s) const;
    connexion_t *getConnexionSortie();

    // Setter
    bool setSortie(Structure *structure);
    void setPositionCarte(const Vector2u &pos);

    bool checkConnexionCircuit(Structure *s, bool commeSortie);

    void afficherStock() const;
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

inline bool Structure::getASortie() const
{
    for (auto c : _connexions)
    {
        if (c.type == TypeConnexion::Output)
            return true;
    }
    return false;
}

inline uint Structure::getNbConnexionsOccupees() const
{
    uint compt = 0;
    for (auto c : _connexions)
    {
        compt += (c.type == TypeConnexion::Input || c.type == TypeConnexion::Output);
    }
    return compt;
}
inline uint Structure::getNbConnexionsLibres() const
{
    uint compt = 0;
    for (auto c : _connexions)
    {
        compt += (c.type == TypeConnexion::Undefined);
    }
    return compt;
}

inline uint Structure::getNbEntrees() const
{
    uint compt = 0;
    for (auto c : _connexions)
    {
        compt += c.type == TypeConnexion::Input;
    }
    return compt;
}
inline connexion_t *Structure::getConnexions() { return _connexions; }
inline bool Structure::getIsStructureConnected(Structure *s) const
{
    for (auto c : _connexions)
    {
        if (c.structure == s)
            return true;
    }
    return false;
}
inline uint Structure::getLevel() const { return _level; }
inline connexion_t *Structure::getConnexionSortie()
{
    for (auto &c : _connexions)
    {
        if (c.type == TypeConnexion::Output)
            return &c;
    }
    return nullptr;
}

inline void Structure::afficherStock() const
{ // Affichage stock
    cout << "Sotck structu " << _idStructure << " : ";
    for (auto r : _stockConnexion)
    {
        // cerr << " - " << ressString[r];
    }
    // cerr << endl;
}

#endif