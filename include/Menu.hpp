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

class ContextGlobal;
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesBoutons;

using namespace std;
using namespace sf;

class Bouton;

class Menu
{
private:
    Vector2f _posEcran;

    vector<Bouton *> _boutonsChoixStructures;
    // Bouton *_boutonsModifTuyau;
    // Bouton *_boutonsModifTuyau;
    // Bouton *_boutonsModifTuyau;

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

    // Setter
    void setPositionEcran(const Vector2f &newPosEcran);
    bool setBoutonsHover(const Vector2f &posMouseEcran);

private:
    void setBoutonsChoixStructures();
    void translaterBoutons(const Vector2f &dirVect);
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
inline Vector2f Menu::getPositionEcran() const { return _posEcran; }

#endif