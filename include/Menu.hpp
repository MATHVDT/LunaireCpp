/**
 * @file Menu.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Prototype des méthodes de la classe Menu
 *
 * @version 0.1
 * @date 2022-09-02
 *
 * @copyright Copyright (c) 2022
 */
#ifndef __MENU_HPP__
#define __MENU_HPP__

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "Stat.hpp"
#include "ContextGlobal.hpp"
#include "Bouton.hpp"
#include "Ressource.hpp"
#include "Batiment.hpp"
// #include "Craft.hpp"

class ContextGlobal;
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesBoutons;

using std::cout;
using std::endl;
using namespace sf;

class Structure;
class Batiment;
class Bouton;
class Stat;

extern string cheminFontBase;

enum SectionMenu
{
    ChoixStructures,
    BatimentSelectCraftDefine,
    BatimentSelectCraftUndefine
};

class Menu
{
private:
    Vector2f _posEcran;

    RectangleShape _lineSeparatorStatBoutons;
    RectangleShape _lineSeparatorMapMenu;
    RectangleShape _lineCoteDroitMenu;

    // Section stat
    Stat *_stat;
    Font _font;

    // Section boutons
    bool _btnActive;
    SectionMenu _sectionMenu;
    vector<Bouton *> _boutonsChoixStructures;
    vector<Bouton *> _boutonBatimentSelect;
    // Bouton *_boutonsModifTuyau;
    // Bouton *_boutonsModifTuyau;
    // Bouton *_boutonsModifTuyau;

    Batiment *_batimentSelect;
    // list<TYPE_RESSOURCE> *_listCraftPossible; // @deprecated ?
    vector<RectangleShape> _tabCraftPossible; // @deprecated ?
    // list<FormuleCraft_t *> _listFormuleCraft; // @deprecated ?
    // vector<RectangleShape> _tabFormuleCraft;
    int _craftHover, _craftSelect;

public: // Static
    static Menu *_singleton;

public: // Static
    static Menu *getInstance();

public:
    Menu();
    ~Menu();

    void init(const Vector2f &posEcran = Vector2f{0.f, 0.f},
              string cheminFont = cheminFontBase);
    void dessiner(float scaleSprite = 1.f);

    // Getter
    Vector2f getPositionEcran() const;
    bool getBoutonsActive() const;
    SectionMenu getSectionMenu() const;
    vector<Bouton *> &getBoutonsSection();
    TYPE_RESSOURCE getRessourceCraftSelect();

    // Setter
    void setPositionEcran(const Vector2f &newPosEcran);
    bool setBoutonsHover(const Vector2f &posMouseEcran);
    bool setBoutonsClick();
    void setBoutonsActive(bool val = true);
    bool resetBoutonsActive();
    bool resetBoutonsHover();

    void setSectionMenu(SectionMenu section);
    // void setListCraftPossible(list<TYPE_RESSOURCE> *listRessCraft); // @deprecated ?
    // void setListFormuleCraft(list<FormuleCraft_t *> listCraft);
    void setBatimentSelect(Batiment *batiment);

private:
    void translaterBoutons(const Vector2f &dirVect);

    void setBoutonsChoixStructures();
    void setBoutonsBatimentSelect();
    void setTabCraftPossible();

    void dessinerBatimentSelectCraftUndefine();
    void dessinerBatimentSelectCraftDefine();

    Structure *getStructureSelect();
    Batiment *getBatimentSelect();
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
// Getter
inline Vector2f Menu::getPositionEcran() const { return _posEcran; }
inline bool Menu::getBoutonsActive() const { return _btnActive; }
inline SectionMenu Menu::getSectionMenu() const { return _sectionMenu; }

// Setter
inline void Menu::setBoutonsActive(bool val) { _btnActive = true; }
// inline void Menu::setListCraftPossible(list<TYPE_RESSOURCE> *listRessCraft)
// {
//     if (_listCraftPossible == nullptr)
//     {
//         _craftSelect = -1;
//     }
//     _listCraftPossible = listRessCraft;
// }
inline void Menu::setBatimentSelect(Batiment *batiment) { _batimentSelect = batiment; }

// inline void Menu::setListFormuleCraft(list<FormuleCraft_t *> listCraft) { _listFormuleCraft = listCraft; }

#endif