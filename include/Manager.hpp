#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include <iostream>
#include <string>
#include <cstring>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "ContextGlobal.hpp"
#include "Carte.hpp"
#include "correspondance.hpp"

#include "Mine.hpp"

class ContextGlobal;
class Carte;
class CaseMap;

extern ContextGlobal *contextGlobal;

using namespace std;
using namespace sf;

enum OVERLAY
{
    CASE_OVER = 0,
    CASE_SELECTIONNEE = 1,
    NB_TEXTURE_OVERLAY = 2
};

class Manager
{
private:
    Carte *_carte;

    Sprite *_spriteCaseOver;
    Sprite *_spriteCaseSelectionnee;

private: // Static
    static Manager *_singleton;

    static uint _tailleTexture;
    static Texture *_texturesManager[NB_TEXTURE_OVERLAY];

public: // Static
    static Manager *getInstance();

    static void chargerMemoireManager();
    static void dechargerMemoireManager();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    ~Manager();
    void init();
    void run();
    void update();

    bool placerStructure();

    void dessiner();

    // Getter

    // Setter
    void setSpriteCaseOver(const Vector2f &position);
    void setSpriteCaseSelectionnee(const Vector2f &position);

private:
    Manager();

    bool placerPipeline(CaseMap *caseSelect, TYPE_STRUCTURE editionStruct);
    bool placerMine(CaseMap *caseSelect, TYPE_STRUCTURE editionStruct);
    bool integrationStructureVoisinage();

    void dessinerOverlay();
    void dessinerOverlayMap();
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

// Setter
inline void Manager::setSpriteCaseOver(const Vector2f &position) { _spriteCaseOver->setPosition(position); }
inline void Manager::setSpriteCaseSelectionnee(const Vector2f &position) { _spriteCaseSelectionnee->setPosition(position); }

#endif