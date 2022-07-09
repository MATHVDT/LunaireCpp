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
uint ContextGlobal::_nbTicksMax = 4; // = 4
Time ContextGlobal::_deltaTick = seconds(0.5f);  // = 25ms

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
    _window.setPosition(Vector2i(50, 50));
    _window.setTitle("Fenetre de objet ContextGlobal");
    _window.setActive();

    _carte = Carte::getInstance();
    _caseOver = nullptr;
    _caseSelectionnee = nullptr;

    _gameEvent = AucunGameEvent;

    _clock.restart();
    _timeSave = _clock.getElapsedTime();
    _tick = 0;

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
        calculCaseOver();
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
    if (_timeSave + _deltaTick <= _clock.getElapsedTime())
    {
        _tick = (_tick + 1) % _nbTicksMax;
        _timeSave = _clock.getElapsedTime();
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
void ContextGlobal::calculCaseOver()
{

    uint largeurMap = _tailleReference / 4 * (3 * _carte->getNbColonnes() + 1);

    Vector2i mousePos = Mouse::getPosition(_window);
    Vector2f mousePosFloat{(float)mousePos.x, (float)mousePos.y};

    if (mousePos.x > 0 &&
        mousePos.x < largeurMap &&
        mousePos.x < _window.getSize().x &&
        mousePos.y > 0 &&
        mousePos.y < _window.getSize().y)
    {
        _caseOver = _carte->getCaseToCoord(mousePosFloat);
    }
    else
    {
        _caseOver = nullptr;
    }
}

/**
 * @brief Set la case selectionnee en fct de la caseOver
 *
 * @param bool - *reset = false*
 */
void ContextGlobal::setCaseSelectionnee(bool reset)
{
    if (reset)
        _caseSelectionnee = nullptr;
    else if (_caseOver != nullptr)
        _caseSelectionnee = _caseOver;
}

/**
 * @brief Actualise le context en fonction de l'event souris
 * @details Bouton gauche -> selection case; Bouton droit sur une case déjà selectionnée -> deselection case
 */
void ContextGlobal::clickSouris()
{
    // Selection case
    if (Mouse::isButtonPressed(Mouse::Left) &&
        _caseOver != _caseSelectionnee)
    { //  bouton gauche souris et changement de case selectionnee
        setCaseSelectionnee(false);
        // cerr << "case select" << endl;
    } // Deselection case
    else if (Mouse::isButtonPressed(Mouse::Right) &&
             _caseOver == _caseSelectionnee)
    { // Test bouton droit souris et caseOver est bien celle selectionnee
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
