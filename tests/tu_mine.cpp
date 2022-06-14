/**
 * @file tu_mine.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Tests Unitaires de la classe Mine
 * 
 * @version 0.1
 * @date 2022-06-09
 * 
 * @copyright Copyright (c) 2022
 */
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
#include "EnumTypeRessource.hpp"
#include "connexion_t.hpp"

using namespace std;
using namespace sf;

TEST_CASE("Test création Mine")
{
    Mine::chargerMemoireMines();

    uint idMaxMines = Mine::getIdMaxMines();
    Mine *m = new Mine(Vector2u(0, 0), TYPE_RESSOURCE::PoussiereRegolite, TYPE_RESSOURCE::PoussiereRegolite);

    REQUIRE(m->getNbMines() == 1);
    REQUIRE(m->getIdMaxMines() == idMaxMines + 1);

    REQUIRE(m->getTypeRessource() == TYPE_RESSOURCE::PoussiereRegolite);

    delete m;
    Mine::dechargerMemoireMines();

}
