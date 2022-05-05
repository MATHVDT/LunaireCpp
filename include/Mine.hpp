#ifndef __MINE_HPP__
#define __MINE_HPP__

#include <iostream>
#include <fstream>
#include <exception>
#include <math.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "enum_sol.hpp"
#include "Batiment.hpp"

// #include "ContextGlobal.hpp"
// #include "enum_ressource.hpp"

using namespace std;
using namespace sf;

extern ContextGlobal &contextGlobal;

extern string cheminFichierTexturesMines;

class Mine : public Batiment
{
private:
    uint _idMine;
    Ressource _typeRessourceSol;
    Ressource _typeRessourceProduite;
    IntRect _zoomTexture;

public: // Static
    static uint _nbMines;
    static uint _idMaxMines;

    static uint _levelMax;
    static uint _nbAnim;

    static uint _tailleTexture;
    static Texture *_texturesMines[NB_RESSOURCES];
    static uint _offsetTextureX; // Largeur d'1 Texture
    static uint _offsetTextureY; // Hauteur

public: // Static
    static uint getNbMines();
    static uint getIdMaxMines();
    static uint getNbAnimMines();
    static uint getLevelMaxMines();

    static void chargerMemoireMines();
    static void dechargerMemoireMines();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Mine(const Vector2u &pos,
         Ressource ressourceSol = Ressource::PoussiereRegolite,
         Ressource ressourceProduite = Ressource::PoussiereRegolite);
    virtual ~Mine() override;

    virtual void init() override; // Va pas servir a mon avis

    virtual void dessiner(float scaleSprite);
    virtual void update() override;

    // Getter
    Ressource getTypeRessource() const;

    // Setter
    void setSpriteTexture(uint tick);

    virtual void process();
    // virtual Ressource livrerStock() override; // Pas besoin de redefinir
    virtual void remplirStock() override;
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint Mine::getNbMines() { return _nbMines; }
inline uint Mine::getIdMaxMines() { return _idMaxMines; }

inline uint Mine::getNbAnimMines() { return _nbAnim; }
inline uint Mine::getLevelMaxMines() { return _levelMax; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline Ressource Mine::getTypeRessource() const { return _typeRessourceProduite; }


#endif