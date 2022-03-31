#include <SFML/Graphics.hpp>
#include "Carte.hpp"
#include "Case.hpp"

void testSFML()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    // sf::Vector2i v{0, 0};

    int nbCase = 4;
    Case::setTailleCase(window, nbCase);
    Carte *carte = Carte::getInstance();
    carte->initCarte(window, nbCase);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        carte->afficher(window);
        // window.draw(shape);
        window.display();
    }
}

int main()
{
    testSFML();

    // Carte::getInstance()->initCarte(10);
    // Carte::getInstance()->afficherConsole();
    // delete Carte::getInstance();
    return 0;
}