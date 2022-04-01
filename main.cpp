#include <SFML/Graphics.hpp>
#include "Carte.hpp"
#include "Case.hpp"

void testSFML()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");

    int nbLignes = 4;
    int nbColonnes = 4;
    Case::setTailleCase(window, nbLignes, nbColonnes);
    Carte *carte = Carte::getInstance();
    carte->initCarte(window, nbLignes, nbColonnes);

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
        cout << endl;
        carte->afficherConsole(cout, true);
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