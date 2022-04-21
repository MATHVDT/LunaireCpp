#ifndef __BATIMENT_HPP__
#define __BATIMENT_HPP__



#include "Structure.hpp"
#include "enum_ressource.hpp"

class Batiment : public Structure
{
private:
    uint _idBatiment;

private: // Static
    static uint _nbBatiments;
    static uint _idMaxBatiments;

protected: // Static
    static const uint _tailleStockEntree;
    static const uint _tailleStockSortie;

public: // Static
    static uint getNbBatiments();
    static uint getIdMaxBatiments();
    static uint getTailleStockEntree();
    static uint getTailleStockSortie();

    static void chargerMemoireBatiments();
    static void dechargerMemoireBatiments();

public:
    Batiment();
    Batiment(const Vector2u &pos,Texture*);
    virtual ~Batiment();

    virtual void init() ;

    virtual void dessiner(float scaleSprite);
    virtual void update();

    // Getter
    uint getIdBatiment() const;
    virtual bool stockEntreePlein() const override;

    virtual void process();

    virtual bool checkConnexionPossible(connexion_t *c) override;
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

inline uint Batiment::getIdBatiment() const { return _idBatiment; }

inline bool Batiment::stockEntreePlein() const { return _stockEntree.size() == _tailleStockEntree; }

#endif