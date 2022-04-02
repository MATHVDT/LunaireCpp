#include <SFML/Graphics.hpp>
#include "Carte.hpp"
#include "Case.hpp"

void testSFML()
{
    float ratio = 16.f / 9.f;
    uint hauteur_fenetre = 800;
    sf::RenderWindow window(sf::VideoMode(hauteur_fenetre * ratio, hauteur_fenetre), "SFML works!", sf::Style::Default);

Case::chargerSprites("ressource/cheminTexturesCases.txt");


    int nbLignes = 1;
    int nbColonnes = 2;
    Case::setTailleCase(window, nbLignes, nbColonnes);
    Carte *carte = Carte::getInstance();
    carte->initCarte(window, nbLignes, nbColonnes);
    // carte->initCarte(window, "./ressource/map.txt");

    // float r = 100.f;
    // float lambda = sqrt(3.f) / 2.f;
    // CircleShape f{r, 6};
    // f.setFillColor(Color::Blue);
    // f.setOrigin(r, r);
    // f.rotate(90);
    // f.setOrigin(0,2*r);
    // f.setPosition(0.f, 0.f);
    // cout << "lambda     : " << lambda << endl;
    // cout << "lambda * r : " << lambda * r << endl;

    // CircleShape p1{3};
    // CircleShape p2{3};

    // p1.setPosition(r, r);
    // // p2.setPosition(2 * lambda * r, 2 * r);
    // // p1.setPosition(lambda*r, r);

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
        // window.draw(f);
        // window.draw(p1);
        // window.draw(p2);
        // carte->afficherConsole(cout, true);
        window.display();
    }
}

int main()
{
    testSFML();

    return 0;
}