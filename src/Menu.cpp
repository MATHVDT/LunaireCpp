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

string cheminFontBase = "./ressource/fonts/nasalization-rg.otf";

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

      _stat(Stat::getInstance()),
      _font(),

      _btnActive(false),
      _sectionMenu(),
      _boutonsChoixStructures{8},
      _boutonBatimentSelect{5},
      //   _listCraftPossible(nullptr),
      _tabCraftPossible{NB_LIGNE_TAB_CRAFT_POSSIBLE * NB_COLONNE_TAB_CRAFT_POSSIBLE},
      //   formuleCraft{nullptr},
      _tabFormuleCraft{NB_COLONNE_TAB_FORMULE_CRAFT},
      _craftHover(-1),
      _craftSelect(-1)
{
}

void Menu::init(const Vector2f &posEcran,
                string cheminFont)
{
    Vector2f dimFenetre = (Vector2f)contextGlobal->getDimensionFenetre();
    Vector2f dimMenu = Vector2f{dimFenetre.x / 3, dimFenetre.y};

    float largeurMap = contextGlobal->getLargeurMapEcran();

    if (!_font.loadFromFile(cheminFont))
    {
        cerr << "Erreur chargement font : " << cheminFont << endl;
    }

    // Stat
    _stat->init(_posEcran,
                dimMenu.x, 0.35f * dimMenu.y,
                _font);

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
    setTabFormuleCraft();

    translaterBoutons(_posEcran);

    // setSectionMenu(SectionMenu::BatimentSelectCraftDefine);
    // setSectionMenu(SectionMenu::ChoixStructures);
    setSectionMenu(SectionMenu::BatimentSelectCraftUndefine);
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
    _stat->dessiner();

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
    { // Dessine tous les btn sauf reset craft
        if (btn->getBoutonType() != BoutonType::boutonResetCraft)
        {
            btn->dessiner();
        }
    }

    // Récupération de la structure selectionnée
    Structure *structSelect = getStructureSelect();
    if (structSelect == nullptr)
        return;

    std::list<TYPE_RESSOURCE> *listCraftPossible = structSelect->getListCraftPossible();

    if (listCraftPossible == nullptr)
        return;

    uint n = listCraftPossible->size();
    TYPE_RESSOURCE r = TYPE_RESSOURCE::Rien;
    auto it = listCraftPossible->begin();

    // liste des ressources craftables
    for (uint i = 0; i < n; ++i)
    {
        // Récupération de la ress craftable
        r = *it;
        ++it;
        _tabCraftPossible[i]
            .setTextureRect(IconeManager::getZoomTextureRessource(r));

        // Contour ressources
        if (i == _craftSelect)
        {
            _tabCraftPossible[i].setOutlineThickness(5.f);
            _tabCraftPossible[i].setOutlineColor(Color::Yellow);
        }
        else if (i == _craftHover)
        {
            _tabCraftPossible[i].setOutlineThickness(5.f);
            _tabCraftPossible[i].setOutlineColor(Color::Cyan);
        }
        else
        {
            _tabCraftPossible[i].setOutlineThickness(.0f);
        }

        contextGlobal->dessinerFenetre(_tabCraftPossible[i]);
    }
}

/**
 * @brief Dessine les boutons lors de la selection d'un batiment AYANT aucun craft définit.
 */
void Menu::dessinerBatimentSelectCraftDefine()
{
    // Affichage boutons
    for (auto &btn : _boutonBatimentSelect)
    { // Dessine tous les btn sauf reset Action
        if (btn->getBoutonType() != BoutonType::boutonValiderCraft)
        {
            btn->dessiner();
        }
    }

    // Récupère la formule de craft
    if (contextGlobal->getBatimentSelect() == nullptr)
        return;

    const std::list<FormuleCraft_t *> *formuleCraft = contextGlobal->getBatimentSelect()->getFormuleCraft();
    if (formuleCraft == nullptr)
    {
        cerr << "Pas de formule de craft à afficher" << endl;
        return;
    }

    // Affichage de la formule de craft
    uint nbEltFormule = formuleCraft->size();

    if (nbEltFormule == 0)
    {
        cerr << "Formule vide, pas d'elt" << endl;
        return;
    }

    std::list<FormuleCraft *>::const_iterator it = formuleCraft->begin();
    uint positionFormule = 0;
    uint index = 0;

    for (auto elt : *formuleCraft)
    { // Pour chaque elt de la formule
        if (elt->produit)
        {
            index = positionFormule++;
        }
        else
        {
            index = NB_COLONNE_TAB_FORMULE_CRAFT - 1;
        }
        _tabFormuleCraft[index].setTextureRect(IconeManager::getZoomTextureRessource(elt->composant));
        contextGlobal->dessinerFenetre(_tabFormuleCraft[index]);
    }
    _tabFormuleCraft[NB_COLONNE_TAB_FORMULE_CRAFT - 2].setTextureRect(IconeManager::getZoomTextureSymbole(SYMBOLE::FlecheDroite));
    contextGlobal->dessinerFenetre(_tabFormuleCraft[NB_COLONNE_TAB_FORMULE_CRAFT - 2]);
}

/*******************************************************/

void Menu::setPositionEcran(const Vector2f &newPosEcran)
{
    Vector2f translation = newPosEcran - _posEcran;
    _posEcran = newPosEcran;

    _stat->translater(translation);

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

/**
 * @brief Definit les positions/tailles/action des boutons BatimentSelect
 *
 */
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
                   Vector2f{0.6f, 0.8f},
                   BoutonState::Normal,
                   GameEvent::ResetCraft};
}

void Menu::setTabCraftPossible()
{
    Vector2f dimFenetre = (Vector2f)contextGlobal->getDimensionFenetre();
    Vector2f dimMenu = Vector2f{dimFenetre.x / 3, dimFenetre.y};
    float largeurMap = contextGlobal->getLargeurMapEcran();

    const Vector2f scaleRessource{0.48f, 0.93f};
    const uint nbLignes = NB_LIGNE_TAB_CRAFT_POSSIBLE;
    const uint nbColonnes = NB_COLONNE_TAB_CRAFT_POSSIBLE;
    const float tailleIcone = 0.08f * dimFenetre.y;
    Vector2f pos;

    for (int k = 0; k < NB_LIGNE_TAB_CRAFT_POSSIBLE * NB_COLONNE_TAB_CRAFT_POSSIBLE; ++k)
    {
        pos.x =
            0.1f * dimMenu.x +
            0.1f * (k % nbColonnes) * dimMenu.y;
        pos.y =
            0.365f * dimMenu.y +
            0.09f * (uint)(k / nbColonnes) * dimMenu.y;

        _tabCraftPossible[k].setSize(Vector2f{tailleIcone, tailleIcone});
        _tabCraftPossible[k].setPosition(pos.x, pos.y);

        _tabCraftPossible[k].setOutlineColor(Color::Yellow);
        _tabCraftPossible[k].setTexture(IconeManager::getTexturesRessource());
    }
}

void Menu::setTabFormuleCraft()
{
    Vector2f dimFenetre = (Vector2f)contextGlobal->getDimensionFenetre();
    Vector2f dimMenu = Vector2f{dimFenetre.x / 3, dimFenetre.y};
    float largeurMap = contextGlobal->getLargeurMapEcran();

    const uint nbColonnes = NB_COLONNE_TAB_FORMULE_CRAFT;
    const float tailleIcone = 0.08f * dimFenetre.y;

    float ecartBordMenu = 0.05 * dimMenu.x;
    float ecartEntreIcone =
        (dimMenu.x - 2 * ecartBordMenu -
         NB_COLONNE_TAB_FORMULE_CRAFT * IconeManager::getLargeurTextureIcone() * tailleIcone) /
        (NB_COLONNE_TAB_FORMULE_CRAFT);

    Vector2f pos{ecartBordMenu, 0.45f * dimMenu.y};

    for (int k = 0; k < NB_COLONNE_TAB_FORMULE_CRAFT; ++k)
    {
        _tabFormuleCraft[k].setSize(Vector2f{tailleIcone, tailleIcone});
        _tabFormuleCraft[k].setPosition(pos.x, pos.y);
        _tabFormuleCraft[k].setTexture(IconeManager::getTexturesRessource());
        pos.x += ecartEntreIcone;
    }
    _tabFormuleCraft[NB_COLONNE_TAB_FORMULE_CRAFT - 2].setTexture(IconeManager::getTexturesSymbole());
    // // Set une case du tableau pour la flèche dans la formule
    // _tabFormuleCraft[NB_COLONNE_TAB_FORMULE_CRAFT - 1].setTextureRect(IconeManager::getZoomTexture(TYPE_RESSOURCE::FlecheDoite));
    // // Swap les 2 dernières cases pour que la dernière dans le tableau soit la flèche
    // auto tmpPosition = _tabFormuleCraft[NB_COLONNE_TAB_FORMULE_CRAFT - 2].getPosition();
    // _tabFormuleCraft[NB_COLONNE_TAB_FORMULE_CRAFT - 2].setPosition(_tabFormuleCraft[NB_COLONNE_TAB_FORMULE_CRAFT - 1].getPosition());
    // _tabFormuleCraft[NB_COLONNE_TAB_FORMULE_CRAFT - 1].setPosition(tmpPosition);
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

    // Translate les tab qui servent au placement des ressources
    // tab des crafts possible
    for (auto &rectShape : _tabCraftPossible)
    {
        Vector2f pos = rectShape.getPosition();
        pos.x += dirVect.x;
        pos.y += dirVect.y;
        rectShape.setPosition(pos);
    }
    // tab de la formule
    for (auto &rectShape : _tabFormuleCraft)
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

void Menu::setSectionMenu(SectionMenu section)
{
    switch (section)
    {
    case SectionMenu::BatimentSelectCraftDefine:
        _boutonBatimentSelect[3]->setState(BoutonState::Disabled); // ValiderCraft
        if (_boutonBatimentSelect[4]->getState() == BoutonState::Disabled)
        {
            _boutonBatimentSelect[4]->setState(BoutonState::Normal); // ResetCraft
        }
        break;
    case SectionMenu::BatimentSelectCraftUndefine:
        if (_boutonBatimentSelect[3]->getState() == BoutonState::Disabled)
        {
            _boutonBatimentSelect[3]->setState(BoutonState::Normal); // ValiderCraft
        }
        _boutonBatimentSelect[4]->setState(BoutonState::Disabled); // ResetCraft
        break;
    default:
        break;
    }
    _sectionMenu = section;
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
                changement = (btn->getState() != BoutonState::Normal);
                btn->setState(BoutonState::Normal);
                changement = true;
            }
        }
    }

    if (_sectionMenu ==
        SectionMenu::BatimentSelectCraftUndefine)
    {
        Rect<float> box;
        // Récupération de la structure selectionnée
        Structure *structSelect = getStructureSelect();
        if (structSelect == nullptr)
            return changement;

        std::list<TYPE_RESSOURCE> *listCraftPossible = structSelect->getListCraftPossible();
        uint n = (listCraftPossible == nullptr ? 0 : listCraftPossible->size());

        for (uint k = 0; k < n; ++k)
        {
            box.width = _tabCraftPossible[k].getSize().x;
            box.height = _tabCraftPossible[k].getSize().y;
            box.left = _tabCraftPossible[k].getPosition().x;
            box.top = _tabCraftPossible[k].getPosition().y;

            if (box.contains(posMouseEcran))
            {
                _craftHover = k;
                changement = true;
            }
            else if (!changement)
            {
                _craftHover = -1;
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

    auto boutons = getBoutonsSection();

    for (auto &btn : boutons)
    {
        if (btn->getState() == BoutonState::Hover)
        {
            btn->setState(BoutonState::Pressed);
            changement = true;
        }
        else if (btn->getState() == BoutonState::Active)
        {
            btn->setState(BoutonState::Normal);
            contextGlobal->setGameEvent(GameEvent::AucunGameEvent);
            _btnActive = false;
            changement = true;
        }
    }

    if (_sectionMenu ==
        SectionMenu::BatimentSelectCraftUndefine)
    {
        Rect<float> box;
        if (_craftHover != -1)
        {
            box.width = _tabCraftPossible[_craftHover].getSize().x;
            box.height = _tabCraftPossible[_craftHover].getSize().y;
            box.left = _tabCraftPossible[_craftHover].getPosition().x;
            box.top = _tabCraftPossible[_craftHover].getPosition().y;

            Vector2f posMouseEcran = contextGlobal->getMouseWorldPos();

            // cerr << "hover : " << _craftHover << " | select : " << _craftSelect << endl;

            // Clic sur une resource
            if (box.contains(posMouseEcran))
            { // Selection / Deselection
                _craftSelect = _craftHover;
                changement = true;
            }
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
/**
 * @brief Remet en normal tous les boutons hover
 *
 * @return true
 * @return false
 */
bool Menu::resetBoutonsHover()
{
    bool changement = false;
    _btnActive = false;

    auto boutons = getBoutonsSection();

    for (auto &btn : boutons)
    {
        if (btn->getState() == BoutonState::Hover)
        {
            btn->setState(BoutonState::Normal);
            changement = true;
        }
    }
    return changement;
}

TYPE_RESSOURCE Menu::getRessourceCraftSelect()
{
    if (_craftSelect == -1)
        return TYPE_RESSOURCE::Rien;

    // Récupération de la structure selectionnée
    Structure *structSelect = getStructureSelect();
    if (structSelect == nullptr)
        return TYPE_RESSOURCE::Rien;

    if (structSelect->getListCraftPossible()->size() < _craftSelect)
    {
        cerr << "Erreur d'indice dans la selection ressource craftables" << endl;
    }
    list<TYPE_RESSOURCE>::iterator itRessource = structSelect->getListCraftPossible()->begin();
    advance(itRessource, _craftSelect);
    return *itRessource;
}

Structure *Menu::getStructureSelect()
{
    CaseMap *caseSelect = contextGlobal->getCaseSelectionnee();
    Structure *structSelect = (caseSelect == nullptr ? nullptr : caseSelect->getConstruction());

    return structSelect;
}

Batiment *Menu::getBatimentSelect()
{
    // @deprecated ? sert a rien du coup ?
    Structure *s = getStructureSelect();
    // Test si c'est un bat craft ?? Manager::isBatimentCraft() ?
}