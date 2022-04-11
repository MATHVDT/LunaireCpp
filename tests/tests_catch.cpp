/**
 * @file tests_catch.cpp
 * @brief
 */
#include "catch.hpp"

#include <fstream>
#include <iostream>

#include "ContextGlobal.hpp"

ContextGlobal &contextGlobal = ContextGlobal::getInstance();

TEST_CASE("Test random")
{
  REQUIRE(5 == 5);
}

// TEST_CASE("Deplacement agent")
// {

//   SECTION("Deplacement Nord Ouest")
//   {
//     REQUIRE(a.getY() == -1);
//   }
// }
