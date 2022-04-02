#include <SFML/Graphics.hpp>
#include "Carte.hpp"

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