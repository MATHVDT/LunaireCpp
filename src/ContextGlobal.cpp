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
    _manager = Manager::getInstance();
    _caseOver = nullptr;
    _caseSelectionnee = nullptr;
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
            setIsRun(false);
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
        // Set le sprite dans le manager
        _manager->setSpriteCaseOver(_caseOver->getPosition());
        _manager->setSpriteCaseSelectionnee(_caseOver->getPosition());
    }
}

/**
 * @brief Actualise le context en fonction de l'event souris
 *
 */
void ContextGlobal::clickSouris()
{

    if (Mouse::isButtonPressed(Mouse::Left))
    {
        setCaseSelectionnee();
    }
    else if (Mouse::isButtonPressed(Mouse::Right))
    {
        setCaseSelectionnee(true);
    }
}

/******************************************************/
