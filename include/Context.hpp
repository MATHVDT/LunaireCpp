#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__

#include <iostream>

class Context
{
    // Static
private:
    static Context _singleton;

public:
    static Context &getInstance();

public:
    ~Context();

private:
    Context();
};

#endif