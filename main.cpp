#include <SFML/Graphics.hpp>
#include "Carte.hpp"
#include "CaseMap.hpp"
#include "Context.hpp"

using namespace std;

#include <iostream>
#include <queue>

void testSFML();
void testQueue();

void printQueue(priority_queue<int *> gq);



int main()
{
    // testSFML();
    // testQueue();



    return 0;
}

void testSFML()
{
    float ratio = 16.f / 9.f;
    uint hauteur_fenetre = 800;
    sf::RenderWindow window(sf::VideoMode(hauteur_fenetre * ratio, hauteur_fenetre), "SFML works!", sf::Style::Default);

    CaseMap::chargerSprites("ressource/cheminTexturesCases.txt");

    int nbLignes = 1;
    int nbColonnes = 1;
    // CaseMap::setScaleCaseMap(window, nbLignes, nbColonnes);

    Carte *carte = Carte::getInstance();
    // carte->initCarte(window, nbLignes, nbColonnes);
    carte->initCarte(window, "./ressource/map.txt");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
            }
        }

        window.clear();
        carte->afficher(window);

        window.display();
    }
    // carte->afficherConsole(cout, true);
}

void testSFML2()
{
    CaseMap::chargerSprites("ressource/cheminTexturesCases.txt");

    float ratio = 16.f / 9.f;
    uint hauteur_fenetre = 800;
    sf::RenderWindow window(sf::VideoMode(hauteur_fenetre * ratio, hauteur_fenetre), "SFML works!", sf::Style::Default);

    int nbLignes = 10;
    int nbColonnes = 2;
    CaseMap::setScaleCaseMap(window, nbLignes, nbColonnes);

    // Declare and load a texture
    sf::Texture texture;
    texture.loadFromFile("ressource/hexagone_regulier_gris.png");
    // Create a sprite
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
    sprite.setColor(sf::Color(255, 255, 255, 200));

    float scale = CaseMap::getTailleCaseMap();
    cout << scale << endl;
    //  scale = 0.5;
    cout << scale << endl;
    cout << sprite.getTextureRect().height << endl;
    sprite.setScale(scale, scale);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                window.close();
        }

        window.clear();

        window.draw(sprite);

        window.display();
    }
}

void printQueue(priority_queue<int *> gq)
{
    priority_queue<int *> g = gq;
    while (!g.empty())
    {
        cout << *g.top() << ", ";
        g.pop();
    }
    cout << '\n';
}
void testQueue()
{
    priority_queue<int *> q{};

    int *un = new int{1};
    int *deux = new int{2};
    int *trois = new int{3};
    int *quatre = new int{4};

    q.push(un);
    q.push(deux);
    q.push(trois);
    q.push(quatre);

    printQueue(q);
    printQueue(q);

    cout << (un < deux) << endl;
    cout << (un > deux) << endl;
    cout << (trois < deux) << endl;
}
