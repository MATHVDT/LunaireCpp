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
      _lineSeparatorStatBoutons(),
      _lineSeparatorMapMenu(),
      _lineCoteDroitMenu(),
      _btnActive(false),
      _sectionMenu(),
      _boutonsChoixStructures{8},
      _boutonBatimentSelect{5},
      _listCraftPossible(nullptr),
      _tabCraftPossible{15}
{
}

void Menu::init(const Vector2f &posEcran)
{
    Vector2f dimFenetre = (Vector2f)contextGlobal->getDimensionFenetre();
    Vector2f dimMenu = Vector2f{dimFenetre.x / 3, dimFenetre.y};

    float largeurMap = contextGlobal->getLargeurMapEcran();

    // Séparation Stat bouton
    _lineSeparatorStatBoutons.setFillColor(Color::White);
    _lineSeparatorStatBoutons.setSize(
        Vector2f(dimMenu.x, 2));
    _lineSeparatorStatBoutons.setPosition(
        largeurMap, 0.35 * dimMenu.y);

    // Contour Menu
    _lineSeparatorMapMenu.setFillColor(Color::White);
    _lineSeparatorMapMenu.setSize(
        Vector2f(2, dimMenu.y));
    _lineSeparatorMapMenu.setPosition(
        Vector2f(largeurMap, 0));

    _lineCoteDroitMenu.setFillColor(Color::White);
    _lineCoteDroitMenu.setSize(
        Vector2f(2, dimMenu.y));
    _lineCoteDroitMenu.setPosition(
        Vector2f(dimFenetre.x - 2, 0));

    setBoutonsChoixStructures();
    setBoutonsBatimentSelect();
    // set les autres btn
    setTabCraftPossible();

    translaterBoutons(_posEcran);

    // setSectionMenu(SectionMenu::BatimentSelectCraftDefine);
    // setSectionMenu(SectionMenu::BatimentSelectCraftUndefine);
    setSectionMenu(SectionMenu::ChoixStructures);
}

Menu::~Menu()
{
    for (auto &btn : _boutonsChoixStructures)
        delete btn;
}

/*******************************************************/

/**
 * @brief Dessine le Menu
 *
 * @param float scaleSprite *(inutile)*
 */
void Menu::dessiner(float scaleSprite)
{
    float scale = contextGlobal->getScaleReference();
    // dessiner Stat

    contextGlobal->dessinerFenetre(_lineSeparatorStatBoutons);
    contextGlobal->dessinerFenetre(_lineSeparatorMapMenu);
    contextGlobal->dessinerFenetre(_lineCoteDroitMenu);

    // if state menu == Choix structure
    switch (_sectionMenu)
    {
    case SectionMenu::ChoixStructures:
        for (auto &btn : _boutonsChoixStructures)
        {
            btn->dessiner();
        }
        break;
    case SectionMenu::BatimentSelectCraftUndefine:
        dessinerBatimentSelectCraftUndefine();
        break;
    case SectionMenu::BatimentSelectCraftDefine:
        dessinerBatimentSelectCraftDefine();
        break;
    default:
        break;
    }
}

/**
 * @brief Dessine les boutons lors de la selection d'un batiment N'AYANT PAS de craft définit.
 */
void Menu::dessinerBatimentSelectCraftUndefine()
{
    for (auto &btn : _boutonBatimentSelect)
    { // Dessine tous les btn sauf reset Action
        if (btn->getBoutonType() != BoutonType::boutonResetCraft)
        {
            btn->dessiner();
        }
    }
    // Afficher les crafts possibles
    // Vector2f posPremiereRessource{};

    // uint nbCrafts = _listCraftPossible->size();
    // for (int k = 0; k < nbCrafts; ++k)
    // {
    //     // Ressource
    // }
    for (auto rectShape : _tabCraftPossible)
    {

        contextGlobal->dessinerFenetre(rectShape);
    }
}

/**
 * @brief Dessine les boutons lors de la selection d'un batiment AYANT aucun craft définit.
 */
void Menu::dessinerBatimentSelectCraftDefine()
{
    for (auto &btn : _boutonBatimentSelect)
    { // Dessine tous les btn sauf reset Action
        if (btn->getBoutonType() != BoutonType::boutonValiderCraft)
        {
            btn->dessiner();
        }
    }
    // Afficher formule
}

/*******************************************************/

void Menu::setPositionEcran(const Vector2f &newPosEcran)
{
    Vector2f translation = newPosEcran - _posEcran;
    _posEcran = newPosEcran;

    // Pour tout les boutons Position += translation
    // btn.deplacerPositionEcran(translation);
    translaterBoutons(translation);
}

/**
 * @brief Definit les positions/tailles/action des boutons Choix structures
 *
 */
void Menu::setBoutonsChoixStructures()
{

    Vector2f dimFenetre = (Vector2f)contextGlobal->getDimensionFenetre();
    Vector2f dimMenu = Vector2f{dimFenetre.x / 3, dimFenetre.y};
    const Vector2f scaleBtn{0.48f, 0.93f};

    _boutonsChoixStructures[0] =
        new Bouton{Vector2f{0.02f * dimMenu.x,
                            0.36f * dimMenu.y},
                   BoutonType::boutonPipeline,
                   scaleBtn,
                   BoutonState::Normal,
                   GameEvent::PlacerPipeline};

    _boutonsChoixStructures[1] =
        new Bouton{Vector2f{0.51f * dimMenu.x,
                            0.36f * dimMenu.y},
                   BoutonType::boutonMarchand,
                   scaleBtn,
                   BoutonState::Normal,
                   GameEvent::PlacerMarchand};

    _boutonsChoixStructures[2] =
        new Bouton{Vector2f{0.02f * dimMenu.x,
                            0.52f * dimMenu.y},
                   BoutonType::boutonMine,
                   scaleBtn,
                   BoutonState::Normal,
                   GameEvent::PlacerMine};

    _boutonsChoixStructures[3] =
        new Bouton{Vector2f{0.51f * dimMenu.x,
                            0.52f * dimMenu.y},
                   BoutonType::boutonFonderie,
                   scaleBtn,
                   BoutonState::Normal,
                   GameEvent::PlacerFonderie};

    _boutonsChoixStructures[4] =
        new Bouton{Vector2f{0.02f * dimMenu.x,
                            0.68f * dimMenu.y},
                   BoutonType::boutonFabrique, scaleBtn,
                   BoutonState::Normal,
                   GameEvent::PlacerFabrique};

    _boutonsChoixStructures[5] =
        new Bouton{Vector2f{0.51f * dimMenu.x,
                            0.68f * dimMenu.y},
                   BoutonType::boutonAtelier,
                   scaleBtn,
                   BoutonState::Normal,
                   GameEvent::PlacerAtelier};

    _boutonsChoixStructures[6] =
        new Bouton{Vector2f{0.02f * dimMenu.x,
                            0.84f * dimMenu.y},
                   BoutonType::boutonCuve,
                   scaleBtn,
                   BoutonState::Normal,
                   GameEvent::PlacerCuve};

    _boutonsChoixStructures[7] =
        new Bouton{Vector2f{0.51f * dimMenu.x,
                            0.84f * dimMenu.y},
                   BoutonType::boutonChantierSpatial,
                   scaleBtn,
                   BoutonState::Normal,
                   GameEvent::PlacerChantierSpatial};
}

void Menu::setBoutonsBatimentSelect()
{
    Vector2f dimFenetre = (Vector2f)contextGlobal->getDimensionFenetre();
    Vector2f dimMenu = Vector2f{dimFenetre.x / 3, dimFenetre.y};
    const Vector2f scaleBtn{0.48f, 0.93f};

    // Upgrade
    _boutonBatimentSelect[0] =
        new Bouton{Vector2f{0.07f * dimMenu.x,
                            0.79f * dimMenu.y},
                   BoutonType::boutonUpgradeStructure,
                   Vector2f{0.42f, 0.8f},
                   BoutonState::Normal,
                   GameEvent::Upgrade};

    // Detruire
    _boutonBatimentSelect[1] =
        new Bouton{Vector2f{0.51f * dimMenu.x,
                            0.79f * dimMenu.y},
                   BoutonType::boutonDetruireStructure,
                   Vector2f{0.42f, 0.8f},
                   BoutonState::Normal,
                   GameEvent::Detruire};

    // Vider Stock
    _boutonBatimentSelect[2] =
        new Bouton{Vector2f{0.07f * dimMenu.x,
                            0.935f * dimMenu.y},
                   BoutonType::boutonViderStock,
                   Vector2f{0.862f, 0.30f},
                   BoutonState::Normal,
                   GameEvent::ViderStock};

    // Valider Craft
    _boutonBatimentSelect[3] =
        new Bouton{Vector2f{0.2f * dimMenu.x,
                            0.645f * dimMenu.y},
                   BoutonType::boutonValiderCraft,
                   Vector2f{0.6f, 0.8f},
                   BoutonState::Normal,
                   GameEvent::ValiderCraft};

    // Reset Craft
    _boutonBatimentSelect[4] =
        new Bouton{Vector2f{0.2f * dimMenu.x,
                            0.645f * dimMenu.y},
                   BoutonType::boutonResetCraft,
                   Vector2f{0.6f, 0.9f},
                   BoutonState::Normal,
                   GameEvent::ResetCraft};
}

void Menu::setTabCraftPossible()
{
    Vector2f dimFenetre = (Vector2f)contextGlobal->getDimensionFenetre();
    Vector2f dimMenu = Vector2f{dimFenetre.x / 3, dimFenetre.y};
    float largeurMap = contextGlobal->getLargeurMapEcran();

    const Vector2f scaleRessource{0.48f, 0.93f};
    const uint nbLignes = 3;
    const uint nbColonnes = 5;
    const float tailleRess = 0.08f * dimFenetre.y;
    Vector2f pos;

    for (int k = 0; k < 15; ++k)
    {
        pos.x =
            0.1f * dimMenu.x +
            0.1f * (k % nbColonnes) * dimMenu.y;
        pos.y =
            0.365f * dimMenu.y +
            0.09f * (uint)(k / nbColonnes) * dimMenu.y;

        _tabCraftPossible[k].setSize(Vector2f{tailleRess, tailleRess});
        _tabCraftPossible[k].setPosition(pos.x, pos.y);

        _tabCraftPossible[k].setFillColor(Color::Blue);
    }
}

void Menu::translaterBoutons(const Vector2f &dirVect)
{
    for (auto &btn : _boutonsChoixStructures)
    {
        btn->deplacerPositionEcran(dirVect);
    }

    // Pour les autres btn
    for (auto &btn : _boutonBatimentSelect)
    {
        btn->deplacerPositionEcran(dirVect);
    }

    for (auto &rectShape : _tabCraftPossible)
    {
        Vector2f pos = rectShape.getPosition();
        pos.x += dirVect.x;
        pos.y += dirVect.y;
        rectShape.setPosition(pos);
    }
}

vector<Bouton *> &Menu::getBoutonsSection()
{

    switch (_sectionMenu)
    {
    case SectionMenu::ChoixStructures:
        return _boutonsChoixStructures;
    case SectionMenu::BatimentSelectCraftDefine:
    case SectionMenu::BatimentSelectCraftUndefine:
        return _boutonBatimentSelect;
    default:
        cerr << "Pas de boutons pour la section : " << _sectionMenu << endl;
        break;
    }
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

    auto boutons = getBoutonsSection();

    for (auto &btn : boutons)
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

    if (_sectionMenu ==
        SectionMenu::BatimentSelectCraftUndefine)
    {
        Rect<float> box;
        for (auto &rectShape : _tabCraftPossible)
        {
            box.width = rectShape.getSize().x;
            box.height = rectShape.getSize().y;
            box.left = rectShape.getPosition().x;
            box.top = rectShape.getPosition().y;

            if (box.contains(posMouseEcran))
            {
                rectShape.setFillColor(Color::Yellow);
            }
            else
            {
                rectShape.setFillColor(Color::Blue);
            }
        }
    }
    // if (_listCraftPossible != nullptr)
    //     cout << _listCraftPossible->size() << endl;

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

    auto boutons = getBoutonsSection();

    for (auto &btn : boutons)
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

    auto boutons = getBoutonsSection();

    for (auto &btn : boutons)
    {
        if (btn->getState() == BoutonState::Active)
        {
            btn->setState(BoutonState::Normal);
            changement = true;
        }
    }
    return changement;
}
