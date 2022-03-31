#include <SFML/Graphics.hpp>
#include "Carte.hpp"

void testSFML()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Vector2i v{0, 0};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

int main()
{
    // testSFML();

    Carte::getInstance()->initCarte(10);

    Carte::getInstance()->afficherConsole();

    delete Carte::getInstance();
    return 0;
}