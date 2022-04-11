#include <iostream>
#include <sstream>
#include <cstring>
#include <list>

#include "catch.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "Structure.hpp"
#include "Batiment.hpp"
#include "Mine.hpp"
#include "direction.hpp"
#include "enum_ressource.hpp"
#include "connexion_t.hpp"

using namespace std;
using namespace sf;

TEST_CASE("Test création Mine")
{
    std::cout << "TU Mine : " << Structure::getNbStructures() << std::endl;
    Mine *m = new Mine(Vector2f(0.f, 0.f), Ressource::MineraiGlace);

    delete m;
}
