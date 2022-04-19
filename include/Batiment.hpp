#ifndef __BATIMENT_HPP__
#define __BATIMENT_HPP__

#include <iostream>
#include <list>
#include <queue>
#include <sys/types.h>

#include "Structure.hpp"
#include "enum_ressource.hpp"

class Batiment : public Structure
{
protected:
    uint _idBatiment;
    list<connexion_t *> _listConnexions;
    bool _sortie;

    queue<Ressource> _stockEntree;
    queue<Ressource> _stockSortie;

private: // Static
    static uint _nbBatiments;
    static uint _idMaxBatiments;
    static const uint _tailleStockEntree;
    static const uint _tailleStockSortie;

public: // Static
    static uint getNbBatiments();
    static uint getIdMaxBatiments();
    static uint getTailleStockEntree();
    static uint getTailleStockSortie();

public:
    Batiment(Vector2f pos, Texture* text);
    virtual ~Batiment();

    virtual void init();

    virtual void dessiner(float scaleSprite);
    virtual void update()=0; // = 0

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

    virtual bool connecte(connexion_t *c) override;
    virtual bool deconnecte(Structure *c) override;

    virtual Ressource livrerStock() override;
    virtual void remplirStock() override;

private:
    bool checkConnexionPossible(connexion_t *c);
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Batiment::getNbBatiments() { return _nbBatiments; }
inline uint Batiment::getIdMaxBatiments() { return _idMaxBatiments; }

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