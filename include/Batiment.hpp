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

// #include <list>
// #include <queue>
#include <typeinfo>

#include "EnumTypeStructure.hpp"

#include "Structure.hpp"
#include "Pipeline.hpp"
#include "ContextGlobal.hpp"
#include "Craft.hpp"
#include <map>
//#include "Mine.hpp"

class ContextGlobal;
class Structure;
class Pipeline;
class Mine;
class Fonderie;
extern ContextGlobal *contextGlobal;


class Batiment : public Structure
{
private:
    uint _idBatiment;
    bool _isFormuleCraftDefine;
    list<TYPE_RESSOURCE> _listRessCraftPossible;
    list<FormuleCraft_t *> *_formuleCraft;
    map<TYPE_RESSOURCE, uint> _stockInterne;

private: // Static
    static uint _nbBatiments;
    static uint _idMaxBatiments;

public: // Static
    static uint getNbBatiments();
    static uint getIdMaxBatiments();

    static void chargerMemoireBatiments();
    static void dechargerMemoireBatiments();

public:
    Batiment();
    Batiment(const Vector2u &pos, Texture *text);
    virtual ~Batiment();

    // Virtual
    virtual void init();

    virtual void dessiner(float scaleSprite) override;
    virtual void setTextureRessourceCraft(TYPE_RESSOURCE ressCraft) = 0;
    virtual void update();
    virtual void process();

    virtual void remplirStock();
    virtual list<TYPE_RESSOURCE> *getListCraftPossible();

    // Gestion des structures connectées
    virtual bool checkConnexionPossible(Structure *s, bool commeSortie) override;
    virtual bool updateOrientation() override;

    // Getter
    uint getIdBatiment() const;
    bool getIsFormuleCraftDefine() const;
    const list<FormuleCraft_t *> *getFormuleCraft() const;
    bool isQuantiteReactifsOk() const;

    // Setter
    void setFormuleCraft(TYPE_RESSOURCE ressCraft);
    void resetFormuleCraft();
    void videStockInterne();
    void transfertStockConnexionToInterne();
    bool ajouterStockInterne(TYPE_RESSOURCE ress);
    bool crafter();

    list<TYPE_RESSOURCE> *checkCraftPossible();
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Batiment::getNbBatiments() { return _nbBatiments; }
inline uint Batiment::getIdMaxBatiments() { return _idMaxBatiments; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

inline uint Batiment::getIdBatiment() const { return _idBatiment; }
inline bool Batiment::getIsFormuleCraftDefine() const { return _isFormuleCraftDefine; }
inline const list<FormuleCraft_t *> *Batiment::getFormuleCraft() const { return _formuleCraft; }

inline list<TYPE_RESSOURCE> *Batiment::getListCraftPossible() { return &_listRessCraftPossible; }

#endif