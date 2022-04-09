#ifndef __BATIMENT_HPP__
#define __BATIMENT_HPP__

#include <iostream>
#include <list>
#include <queue>
#include <sys/types.h>

#include "Structure.hpp"
#include "direction.hpp"
#include "connexion_t.hpp"

class Batiment : public Structure
{
protected:
    uint _idBatiment;
    list<connexion_t *> _listConnexions;
    bool _sortie;


private: // Static
    static uint _nbBatiments;
    static const uint _tailleStockEntree;
    static const uint _tailleStockSortie;

public: // Static
    static uint getNbBatiments();
    static uint getTailleStockEntree();
    static uint getTailleStockSortie();

public:
    Batiment(Vector2f pos);
    virtual ~Batiment();

    virtual void init();

    virtual void dessiner(float scaleSprite);
    virtual void update();

    // Getter
    bool getASortie() const;
    uint getNbConnexions() const;
    uint getNbEntrees() const;
    uint getIdBatiment() const;
    list<connexion_t *> getConnexionsEntrantes() const;
    list<connexion_t *> getConnexions() const;
    connexion_t *getConnexionSortie() const;
    connexion_t *getConnexionDirection(const Vector2i &dir) const;
    connexion_t *getConnexionDirection(int DIRECTION) const;

    // Setter
    void setSortie(Structure *structure);

    // Gestion connextion_t
    void deconnecterStructure(Structure *structure);
    void deconnecterStructure(connexion_t *c);

    bool ajouterConnexion(connexion_t *c);

private:
    bool checkConnexionPossible(connexion_t *c);

    virtual bool connecte(connexion_t *c) override;
    virtual bool deconnecte(Structure *c) override;
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Batiment::getNbBatiments() { return _nbBatiments; }

inline uint Batiment::getTailleStockEntree() { return _tailleStockEntree; }
inline uint Batiment::getTailleStockSortie() { return _tailleStockSortie; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline bool Batiment::getASortie() const { return _sortie; }

inline uint Batiment::getNbConnexions() const { return _listConnexions.size(); }
inline uint Batiment::getNbEntrees() const { return getNbConnexions() - _sortie; }

inline uint Batiment::getIdBatiment() const { return _idBatiment; }

#endif