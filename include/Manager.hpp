#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include "Carte.hpp"

class Manager
{
private:
   Carte * _carte;
public:
    Manager(Carte *carte);
    ~Manager();
};



#endif