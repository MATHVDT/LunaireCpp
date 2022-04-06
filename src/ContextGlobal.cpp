#include "ContextGlobal.hpp"

ContextGlobal ContextGlobal::_singleton{};

ContextGlobal::ContextGlobal() { std::cout << "Création contextGlobal" << std::endl; }

ContextGlobal::~ContextGlobal()
{
    _window.close();
    std::cout << "Destruction contextGlobal" << std::endl;
}

ContextGlobal &ContextGlobal::getInstance() { return _singleton; }

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
