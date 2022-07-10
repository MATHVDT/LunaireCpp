/**
 * @file tu_pipeline.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Tests Unitaires de la classe Pipeline
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

#include "Pipeline.hpp"

#include "ContenuPipeline.hpp"
#include "Mine.hpp"
#include "direction.hpp"
#include "EnumTypeRessource.hpp"
#include "connexion_t.hpp"

using namespace std;
using namespace sf;

TEST_CASE("Test création Pipeline")
{
    Pipeline::chargerMemoirePipelines();
    ContenuPipeline::chargerMemoireTypeRessource();

    uint idMaxPipelines = Pipeline::getIdMaxPipelines();
    Pipeline *pipe = new Pipeline{Vector2u(0, 0)};

    REQUIRE(pipe->getNbPipelines() == 1);
    REQUIRE(pipe->getIdMaxPipelines() == idMaxPipelines + 1);

    delete pipe;
    Pipeline::dechargerMemoirePipelines();
    ContenuPipeline::dechargerMemoireTypeRessource();
}
