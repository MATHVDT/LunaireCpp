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
                   GameEvent::PlacerPipeline};

    _boutonsChoixStructures[1] =
        new Bouton{Vector2f{0.51f * dimMenu.x, 0.27f * dimMenu.y},
                   BoutonType::boutonMarchand,
                   BoutonState::Normal,
                   GameEvent::PlacerMarchand};

    _boutonsChoixStructures[2] =
        new Bouton{Vector2f{0.02f * dimMenu.x, 0.45f * dimMenu.y},
                   BoutonType::boutonMine,
                   BoutonState::Normal,
                   GameEvent::PlacerMine};

    _boutonsChoixStructures[3] =
        new Bouton{Vector2f{0.51f * dimMenu.x, 0.45f * dimMenu.y},
                   BoutonType::boutonFonderie,
                   BoutonState::Normal,
                   GameEvent::PlacerFonderie};

    _boutonsChoixStructures[4] =
        new Bouton{Vector2f{0.02f * dimMenu.x, 0.63f * dimMenu.y},
                   BoutonType::boutonFabrique,
                   BoutonState::Normal,
                   GameEvent::PlacerFabrique};

    _boutonsChoixStructures[5] =
        new Bouton{Vector2f{0.51f * dimMenu.x, 0.63f * dimMenu.y},
                   BoutonType::boutonAtelier,
                   BoutonState::Normal,
                   GameEvent::PlacerAtelier};

    _boutonsChoixStructures[6] =
        new Bouton{Vector2f{0.02f * dimMenu.x, 0.81f * dimMenu.y},
                   BoutonType::boutonCuve,
                   BoutonState::Normal,
                   GameEvent::PlacerCuve};

    _boutonsChoixStructures[7] =
        new Bouton{Vector2f{0.51f * dimMenu.x, 0.81f * dimMenu.y},
                   BoutonType::boutonChantierSpatial,
                   BoutonState::Normal,
                   GameEvent::PlacerChantierSpatial};
}

void Menu::translaterBoutons(const Vector2f &dirVect)
{
    for (auto &btn : _boutonsChoixStructures)
    {
        btn->deplacerPositionEcran(dirVect);
    }

    // Pour les autres btn
}

/**
 * @brief Change l'état des boutons s'il y a la souris dessus
 *
 * @param const Vector2f & - *posMouseEcran*
 * @return true - *1 bouton hover*
 * @return false - *0 bouton hover
 */
bool Menu::setBoutonsHover(const Vector2f &posMouseEcran)
{
    bool changement = false;
    for (auto &btn : _boutonsChoixStructures)
    {
        if (btn->getState() == BoutonState::Pressed)
        {
            if (btn->checkIn(posMouseEcran) &&
                !Mouse::isButtonPressed(Mouse::Left))
            {
                resetBoutonsActive();
                btn->setState(BoutonState::Active);
                contextGlobal->setGameEvent(btn->getAction());
                _btnActive = true;
                changement = true;
            }
        }
        else if (
            btn->getState() != BoutonState::Active &&
            btn->getState() != BoutonState::Disabled)
        {
            if (btn->checkIn(posMouseEcran))
            {
                btn->setState(BoutonState::Hover);
                changement = true;
            }
            else // Pas la souris dessus
            {
                changement = btn->getState() != BoutonState::Normal;
                btn->setState(BoutonState::Normal);
            }
        }
    }
    return changement;
}

/**
 * @brief Change l'état des boutons s'il y a un click de la souris dessus
 *
 * @param const Vector2f & - *posMouseEcran*
 * @return true - *1 bouton hover*
 * @return false - *0 bouton hover*
 */
bool Menu::setBoutonsClick()
{
    // Mouse::isButtonPressed(Mouse::Left)
    bool changement = false;
    for (auto &btn : _boutonsChoixStructures)
    {
        if (btn->getState() == BoutonState::Hover)
        {
            btn->setState(BoutonState::Pressed);
            changement = true;
        }
        if (btn->getState() == BoutonState::Active)
        {
            btn->setState(BoutonState::Normal);
            contextGlobal->setGameEvent(GameEvent::AucunGameEvent);
            _btnActive = false;
            changement = true;
        }
    }
    return changement;
}

/**
 * @brief Remet en normal tous les boutons activés
 *
 * @return true
 * @return false
 */
bool Menu::resetBoutonsActive()
{
    bool changement = false;
    _btnActive = false;
    for (auto &btn : _boutonsChoixStructures)
    {
        if (btn->getState() == BoutonState::Active)
        {
            btn->setState(BoutonState::Normal);
            changement = true;
        }
    }
    return changement;
}
