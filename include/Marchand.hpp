#ifndef __MARCHAND_HPP__
#define __MARCHAND_HPP__

#include "Batiment.hpp"
extern ContextGlobal *contextGlobal;

extern string cheminFichierMarchand;

class Marchand : public Batiment
{

private: // Static
    static Texture *_textureMarchand;

public: // Static
    static void chargerMemoireMarchand();
    static void dechargerMemoireMarchand();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    Marchand(const Vector2u &pos);

    virtual ~Marchand();

    virtual void init() override;

    virtual void dessiner(float scaleSprite) override;
    virtual void update() override;
    virtual void setTextureRessourceCraft(TYPE_RESSOURCE ressCraft) override;

    virtual void process() override;

    virtual bool checkConnexionPossible(Structure *s, bool commeSortie) override;
    virtual bool updateOrientation() override ;
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/
inline void Marchand::setTextureRessourceCraft(TYPE_RESSOURCE ressCraft) { return; }

#endif