#ifndef __MASTER_BATIMENT_HPP__
#define __MASTER_BATIMENT_HPP__

#include "Batiment.hpp"
extern ContextGlobal *contextGlobal;

extern string cheminFichierMasterBatiment;

class MasterBatiment : public Batiment
{

private:                            // Static
    static uint _tailleStockEntree; // = 6
    static uint _tailleStockSortie; // = 0
    static Texture *_textureMasterBatiment;

public: // Static
    static uint getTailleStockEntreeMasterBatiment();
    static uint getTailleStockSortieMasterBatiment();

    static void chargerMemoireMasterBatiment();
    static void dechargerMemoireMasterBatiment();

private: // Static
    static void chargerTextures(string fichierCheminsTexture);

public:
    MasterBatiment(const Vector2u &pos);

    virtual ~MasterBatiment();

    virtual void init() override;

    virtual void dessiner(float scaleSprite) override;
    virtual void update() override;

    virtual void process() override;

    virtual bool updateOrientation() override;
    virtual bool checkConnexionPossible(Structure *s, bool commeSortie) override;
};

/***************************************************/
/*                 Méthodes inline                 */
/***************************************************/

/***************************************************/
/*              Méthodes inline static             */
/***************************************************/
inline uint MasterBatiment::getTailleStockEntreeMasterBatiment() { return _tailleStockEntree; }
inline uint MasterBatiment::getTailleStockSortieMasterBatiment() { return _tailleStockSortie; }

/***************************************************/
/*           Méthodes inline non static            */
/***************************************************/

#endif