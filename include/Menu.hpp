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

#include "ContextGlobal.hpp"

class ContextGlobal;
extern ContextGlobal *contextGlobal;

extern string cheminFichierTexturesBoutons;

using namespace std;
using namespace sf;

class Menu
{
private:
    //

public:
    Menu();
    ~Menu();

    void dessiner(float scaleSprite = 1.f);
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

#endif