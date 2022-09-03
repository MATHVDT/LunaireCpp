/**
 * @file contextGlobal->cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe ContextGlobal
 *
 * @version 0.1
 * @date 2022-06-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ContextGlobal.hpp"

ContextGlobal *ContextGlobal::_singleton = ContextGlobal::getInstance();
uint ContextGlobal::_nbTicksMax = 4;             // = 4
Time ContextGlobal::_deltaTick = seconds(0.25f); // = 25ms

ContextGlobal::ContextGlobal()
{
    std::cout << std::endl
              << "Création contextGlobal" << std::endl
              << std::endl
              << std::endl;
}

ContextGlobal::~ContextGlobal()
{
    _window.close();
    delete _carte;
    delete _menu;
    std::cout << "Destruction contextGlobal" << std::endl;
}

/**
 * @brief Récupère ou crée un instance du ContextGlobal *(patron de singleton)*
 * @warning Penser à delete le singleton
 * @return ContextGlobal * - *_singleton*
 */
ContextGlobal *ContextGlobal::getInstance()
{
    // Pas d'instance créée => alors création
    if (ContextGlobal::_singleton == nullptr)
        _singleton = new ContextGlobal{};
    return _singleton;
}

/**
 * @brief Initialise le contextGlobal, en créant la fenêtre et les autres paramètres
 *
 * @param const Vector2y& - *dimFenetre*
 */
void ContextGlobal::init(const Vector2u &dimFenetre)
{
    // Initialisation des attributs
    _ratioFenetre = dimFenetre.x / dimFenetre.y;
    _dimensionFenetre = dimFenetre;
    _isRun = true;

    // Initialisation fenêtre
    _window.create(VideoMode(_dimensionFenetre.x,
                             _dimensionFenetre.y),
                   "SFML works!",
                   sf::Style::Default);
    _window.setPosition(Vector2i(100, 50));
    _window.setTitle("Fenetre de objet ContextGlobal");
    _window.setActive();

    _carte = Carte::getInstance();
    _menu = Menu::getInstance();
    _caseHover = nullptr;
    _caseSelectionnee = nullptr;

    _gameEvent = AucunGameEvent;

    _clock.restart();
    _timeSaveTick = _clock.getElapsedTime();
    _tick = 0;
    _updateTick = true;

    _editionStructureSelectionnee = TYPE_STRUCTURE::AucuneStructure;
}

/**
 * @brief Actualise le renderer de la fenêtre
 */
void ContextGlobal::afficherFenetre()
{
    _window.display();
    _window.clear();
}

/**
 * @brief Tient à jour le contextGlobal du jeu...
 */
void ContextGlobal::update()
{

    // Vérification des l'events "system" => fermer fenetre
    if (_event.type == sf::Event::Closed)
        setIsRun(false);
    if (_event.type == sf::Event::KeyPressed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            setIsRun(false);
        }
        else
        {
            checkClavierStructures();
        }
    }

    if (_event.type == sf::Event::MouseMoved)
    {
        if (getMouseWorldPos().x < getLargeurMapEcran())
        {
            calculCaseHover();
        }
        else
        {
            _caseHover = nullptr;
            calculMenuHover();
        }
    }
    if (_event.type == sf::Event::MouseButtonPressed)
    {
        clickSouris();
    }
    // cout << "Mouse : " << Mouse::getPosition().x << ", " << Mouse::getPosition().y << endl;
    // Vector2i mousePos = Mouse::getPosition();
    // cout << "mapCoordsToPixel : " << _window.mapCoordsToPixel((Vector2f)mousePos).x << ", " << _window.mapCoordsToPixel((Vector2f)mousePos).y << endl;
    // cout << "mapPixelToCoords : " << _window.mapPixelToCoords(mousePos).x << ", " << _window.mapPixelToCoords(mousePos).y << endl;

    // Calcul du tick
    if (_timeSaveTick + _deltaTick <= _clock.getElapsedTime())
    {
        _tick = (_tick + 1) % _nbTicksMax;
        _timeSaveTick = _clock.getElapsedTime();
        _updateTick = true;
    }
}

/**
 * @brief Dessine un objet dans la fenêtre
 *
 * @param const Drawable & - *obj*
 */
void ContextGlobal::dessinerFenetre(const Drawable &obj)
{
    _window.draw(obj);
}

/**
 * @brief Calcule la largeur d'écran prise par la carte
 *
 * @return float - *largeur d'écran de la carte*
 */
float ContextGlobal::getLargeurMapEcran() const
{
    // return (float)(_tailleReference / 4 * (3 * _carte->getNbColonnes() + 1));
    return 2 * _dimensionFenetre.x / 3;
}

/**
 * @brief Dessine un objet dans la fenêtre
 *
 * @param const Drawable * - *obj*
 */
void ContextGlobal::dessinerFenetre(const Drawable *obj) { dessinerFenetre(*obj); }

/******************************************************/

/**
 * @brief Calcule la case survolée par la souris
 *
 */
void ContextGlobal::calculCaseHover()
{

    uint largeurMap = getLargeurMapEcran();

    const Vector2f worldPos = getMouseWorldPos();

    // Affichage coord souris
    // cout << "souris pos : " << worldPos.x << ", " << worldPos.y << endl;

    if (worldPos.x > 0 &&
        worldPos.x < largeurMap &&
        worldPos.x < _window.getSize().x &&
        worldPos.y > 0 &&
        worldPos.y < _window.getSize().y)
    {
        _caseHover = _carte->getCaseToCoord(worldPos);
    }
}

/**
 * @brief Calcul la case survolée sur le menu
 *
 */
void ContextGlobal::calculMenuHover()
{
    uint largeurMap = getLargeurMapEcran();
    const Vector2f worldPos = getMouseWorldPos();

    // Dans le menu
    if (worldPos.x > largeurMap &&
        worldPos.x < _window.getSize().x &&
        worldPos.y > 0 &&
        worldPos.y < _window.getSize().y)
    {
        _menu->setBoutonsHover(worldPos);
    }
}

/**
 * @brief Set la case selectionnee en fct de la caseHover
 *
 * @param bool - *reset = false*
 */
void ContextGlobal::setCaseSelectionnee(bool reset)
{
    if (reset)
        _caseSelectionnee = nullptr;
    else if (_caseHover != nullptr)
        _caseSelectionnee = _caseHover;
}

/**
 * @brief Actualise le context en fonction de l'event souris
 * @details Bouton gauche -> selection case; Bouton droit sur une case déjà selectionnée -> deselection case
 */
void ContextGlobal::clickSouris()
{
    // Selection case
    if (Mouse::isButtonPressed(Mouse::Left) &&
        _caseHover != _caseSelectionnee)
    { //  bouton gauche souris et changement de case selectionnee
        setCaseSelectionnee(false);
        // cerr << "case select" << endl;
    } // Deselection case
    else if (Mouse::isButtonPressed(Mouse::Right) &&
             _caseHover == _caseSelectionnee)
    { // Test bouton droit souris et caseHover est bien celle selectionnee
        setCaseSelectionnee(true);
    }
}

/******************************************************/

/**
 * @brief Set la structure a construire
 *
 */
void ContextGlobal::checkClavierStructures()
{
    switch (_event.key.code)
    {
    case Keyboard::A:
        _editionStructureSelectionnee = TYPE_STRUCTURE::MinePoussiereRegolite;
        // cerr << "MinePoussiereRegolite selectionnée" << endl;
        break;
    case Keyboard::B:
        _editionStructureSelectionnee = TYPE_STRUCTURE::Pipeline;
        // cerr << "Pipeline selectionnée" << endl;
        break;
    case Keyboard::C:
        _editionStructureSelectionnee = TYPE_STRUCTURE::MasterBatiment;
        // cerr << "MasterBatiment selectionnée" << endl;
        break;
    case Keyboard::Space:
        _editionStructureSelectionnee = TYPE_STRUCTURE::AucuneStructure;
        // cerr << "AucuneStructure selectionnée" << endl;
    case Keyboard::I:
        _gameEvent = InverserSensPipeline;
        break;
    default:
        break;
    }
}
