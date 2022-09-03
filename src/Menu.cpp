/**
 * @file Menu.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Menu
 *
 * @version 0.1
 * @date 2022-09-02
 *
 * @copyright Copyright (c) 2022
 */
#include "Menu.hpp"

Menu *Menu::_singleton = nullptr;

/**
 * @brief Récupère ou crée un instance de la Menu *(patron de singleton)*
 * @warning Penser à delete le singleton
 * @return Menu* - *_singleton*
 */
Menu *Menu::getInstance()
{
    // Pas d'instance créée => alors création
    if (Menu::_singleton == nullptr)
        _singleton = new Menu{};
    return _singleton;
}

Menu::Menu()
    : _posEcran(Vector2f{0.f, 0.f}),
      _boutonsChoixStructures{8}
{
}

void Menu::init(const Vector2f &posEcran)
{
    setBoutonsChoixStructures();
    // set les autres btn

    translaterBoutons(_posEcran);
}

Menu::~Menu()
{
    for (auto &btn : _boutonsChoixStructures)
        delete btn;
}

void Menu::dessiner(float scaleSprite)
{
    float scale = contextGlobal->getScaleReference();
    // dessiner Stat

    // if state menu == Choix structure
    for (auto &btn : _boutonsChoixStructures)
    {
        btn->dessiner(scale);
    }
}

void Menu::setPositionEcran(const Vector2f &newPosEcran)
{
    Vector2f translation = newPosEcran - _posEcran;
    _posEcran = newPosEcran;

    // Pour tout les boutons Position += translation
    // btn.deplacerPositionEcran(translation);
    translaterBoutons(translation);
}

void Menu::setBoutonsChoixStructures()
{

    Vector2f dimFenetre = (Vector2f)contextGlobal->getDimensionFenetre();
    Vector2f dimMenu = Vector2f{dimFenetre.x / 3, dimFenetre.y};

    _boutonsChoixStructures[0] =
        new Bouton{Vector2f{0.02f * dimMenu.x, 0.27f * dimMenu.y},
                   BoutonType::boutonPipeline,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[1] =
        new Bouton{Vector2f{0.51f * dimMenu.x, 0.27f * dimMenu.y},
                   BoutonType::boutonMarchand,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[2] =
        new Bouton{Vector2f{0.02f * dimMenu.x, 0.45f * dimMenu.y},
                   BoutonType::boutonMine,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[3] =
        new Bouton{Vector2f{0.51f * dimMenu.x, 0.45f * dimMenu.y},
                   BoutonType::boutonFonderie,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[4] =
        new Bouton{Vector2f{0.02f * dimMenu.x, 0.63f * dimMenu.y},
                   BoutonType::boutonFabrique,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[5] =
        new Bouton{Vector2f{0.51f * dimMenu.x, 0.63f * dimMenu.y},
                   BoutonType::boutonAtelier,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[6] =
        new Bouton{Vector2f{0.02f * dimMenu.x, 0.81f * dimMenu.y},
                   BoutonType::boutonCuve,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[7] =
        new Bouton{Vector2f{0.51f * dimMenu.x, 0.81f * dimMenu.y},
                   BoutonType::boutonChantierSpatial,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};
}

void Menu::translaterBoutons(const Vector2f &dirVect)
{
    for (auto &btn : _boutonsChoixStructures)
    {
        btn->deplacerPositionEcran(dirVect);
    }

    // Pour les autres btn
}

bool Menu::setBoutonsHover(const Vector2f &posMouseEcran)
{
}
