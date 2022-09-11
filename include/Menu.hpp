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

#include "vector"

#include "ContextGlobal.hpp"
#include "Bouton.hpp"
// #include "Structure.hpp"
// #include "Batiment.hpp"
#include "Ressource.hpp"

class ContextGlobal;
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesBoutons;

using namespace std;
using namespace sf;

class Structure;
class Batiment;
class Bouton;

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

    bool _btnActive;
    SectionMenu _sectionMenu;
    vector<Bouton *> _boutonsChoixStructures;
    vector<Bouton *> _boutonBatimentSelect;
    // Bouton *_boutonsModifTuyau;
    // Bouton *_boutonsModifTuyau;
    // Bouton *_boutonsModifTuyau;
    list<TYPE_RESSOURCE> *_listCraftPossible;
    vector<RectangleShape> _tabCraftPossible;
    

public: // Static
    static Menu *_singleton;

public: // Static
    static Menu *getInstance();

public:
    Menu();
    ~Menu();

    void init(const Vector2f &posEcran = Vector2f{0.f, 0.f});
    void dessiner(float scaleSprite = 1.f);

    // Getter
    Vector2f getPositionEcran() const;
    bool getBoutonsActive() const;
    SectionMenu getSectionMenu() const;
    vector<Bouton *> &getBoutonsSection();

    // Setter
    void setPositionEcran(const Vector2f &newPosEcran);
    bool setBoutonsHover(const Vector2f &posMouseEcran);
    bool setBoutonsClick();
    void setBoutonsActive(bool val = true);
    bool resetBoutonsActive();

    void setSectionMenu(SectionMenu section);
    void setListCraftPossible(list<TYPE_RESSOURCE> *listRessCraft);

private:
    void translaterBoutons(const Vector2f &dirVect);

    void setBoutonsChoixStructures();
    void setBoutonsBatimentSelect();
    void setTabCraftPossible();

    void dessinerBatimentSelectCraftUndefine();
    void dessinerBatimentSelectCraftDefine();
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
inline void Menu::setSectionMenu(SectionMenu section) { _sectionMenu = section; }
inline void Menu::setListCraftPossible(list<TYPE_RESSOURCE> *listRessCraft) { _listCraftPossible = listRessCraft; }

#endif