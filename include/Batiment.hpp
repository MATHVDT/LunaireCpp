/**
 * @file Batiment.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Batiment
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __BATIMENT_HPP__
#define __BATIMENT_HPP__

#include <list>
#include <queue>
#include <typeinfo>

#include "Structure.hpp"
#include "Pipeline.hpp"
#include "ContextGlobal.hpp"

class ContextGlobal;
class Pipeline;

extern ContextGlobal *contextGlobal;

class Batiment : public Structure
{
private:
    uint _idBatiment;

private: // Static
    static uint _nbBatiments;
    static uint _idMaxBatiments;

protected:                                // Static
    static const uint _tailleStockEntree; // = 6 defaut
    static const uint _tailleStockSortie; // = 1

public: // Static
    static uint getNbBatiments();
    static uint getIdMaxBatiments();
    static uint getTailleStockEntree();
    static uint getTailleStockSortie();

    static void chargerMemoireBatiments();
    static void dechargerMemoireBatiments();

public:
    Batiment();
    Batiment(const Vector2u &pos,
             Texture *,
             uint tailleStockEntree = _tailleStockEntree,
             uint tailleStockSortie = _tailleStockSortie);
    virtual ~Batiment();

    virtual void init();

    virtual void dessiner(float scaleSprite);
    virtual void update();

    // Getter
    uint getIdBatiment() const;

    virtual void process();

    bool updateOrientation() override;
    virtual bool checkConnexionPossible(Structure *s, bool commeSortie) override;
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

#endif