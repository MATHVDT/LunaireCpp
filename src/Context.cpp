#include "Context.hpp"

Context Context::_singleton{};

Context::Context() { std::cout << "Création context" << std::endl; }

Context::~Context() { std::cout << "Destruction context" << std::endl; }

Context &Context::getInstance()
{
    return _singleton;
}

void Context::init() {}
