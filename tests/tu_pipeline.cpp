#include <iostream>
#include <sstream>
#include <cstring>
#include <list>

#include "catch.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "Pipeline.hpp"

#include "Mine.hpp"
#include "direction.hpp"
#include "enum_ressource.hpp"
#include "connexion_t.hpp"

using namespace std;
using namespace sf;

TEST_CASE("Test création Pipeline")
{
    Pipeline::chargerMemoirePipelines();

    uint idMaxPipelines = Pipeline::getIdMaxPipelines();
    Pipeline *pipe = new Pipeline{Vector2u(0, 0)};

    REQUIRE(pipe->getNbPipelines() == 1);
    REQUIRE(pipe->getIdMaxPipelines() == idMaxPipelines + 1);

    delete pipe;
    Pipeline::dechargerMemoirePipelines();
}
