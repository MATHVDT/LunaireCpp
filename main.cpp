#include <SFML/Graphics.hpp>
#include "Carte.hpp"
#include "Case.hpp"

void testSFML()
{
    float ratio = 16.f / 9.f;
    uint hauteur_fenetre = 600;
    sf::RenderWindow window(sf::VideoMode(hauteur_fenetre * ratio, hauteur_fenetre), "SFML works!", sf::Style::Default);

    int nbLignes = 4;
    int nbColonnes = 6;
    Case::setTailleCase(window, nbLignes, nbColonnes);
    Carte *carte = Carte::getInstance();
    carte->initCarte(window, nbLignes, nbColonnes);
    carte->initCarte(window, "./ressource/map.txt");

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
        // carte->afficherConsole(cout, true);
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