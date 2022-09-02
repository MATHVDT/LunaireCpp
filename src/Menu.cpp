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

Menu::Menu(const Vector2f &posEcran)
    : _posEcran(posEcran),
      _boutonsChoixStructures{8}
{
    setBoutonsChoixStructures();
    // set les autres btn

    translaterBoutons(_posEcran);
}

Menu::~Menu() {}

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
    _boutonsChoixStructures[0] =
        new Bouton{Vector2f{10.f, 400.f},
                   BoutonType::boutonPipeline,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[1] =
        new Bouton{Vector2f{230.f, 400.f},
                   BoutonType::boutonMarchand,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[2] =
        new Bouton{Vector2f{10.f, 520.f},
                   BoutonType::boutonMine,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[3] =
        new Bouton{Vector2f{230.f, 520.f},
                   BoutonType::boutonFonderie,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[4] =
        new Bouton{Vector2f{10.f, 640.f},
                   BoutonType::boutonFabrique,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[5] =
        new Bouton{Vector2f{230.f, 640.f},
                   BoutonType::boutonAtelier,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[6] =
        new Bouton{Vector2f{10.f, 760.f},
                   BoutonType::boutonCuve,
                   BoutonState::Normal,
                   GameEvent::AucunGameEvent};

    _boutonsChoixStructures[7] =
        new Bouton{Vector2f{230.f, 760.f},
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
