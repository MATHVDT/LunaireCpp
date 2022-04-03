#include <iostream>
#include <sstream>
#include <cstring>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "catch.hpp"

#include "Structure.hpp"

#include "Carte.hpp"
#include "CaseMap.hpp"
#include "ContextGlobal.hpp"

using namespace std;
using namespace sf;

ContextGlobal &contextGlobal = ContextGlobal::getInstance();