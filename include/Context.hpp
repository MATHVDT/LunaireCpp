#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__

#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include "enum_sol.hpp"

class Context
{

private:
    uint _hauteurFenetre;
    uint _largeurFenetre;

    // Static
private:
    static Context _singleton;

public:
    static Context &getInstance();

public:
    ~Context();

    void init();

private:
    Context();
};

#endif