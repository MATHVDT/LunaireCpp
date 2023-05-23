/**
 * @file IconeManager.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe IconeManager
 *
 * @version 0.1
 * @date 2022-09-10
 *
 * @copyright Copyright (c) 2022
 */
#include "IconeManager.hpp"

string cheminFichierTexturesRessources = "ressource/cheminTextures/cheminTexturesTypeRessource.txt";
string cheminFichierTexturesSymboles = "ressource/cheminTextures/cheminTexturesSymbole.txt";

IntRect IconeManager::_zoomTexture{};
float IconeManager::_largeurTextureIcone = 0;
float IconeManager::_hauteurTextureIcone = 0;

// Ressource
uint IconeManager::_nbRessources = NB_RESSOURCES;
Texture *IconeManager::_texturesRessource = nullptr;
Sprite *IconeManager::_spritesRessource = nullptr;

// Symbole
uint IconeManager::_nbSymboles = NB_SYMBOLES;
Texture *IconeManager::_texturesSymbole = nullptr;
Sprite *IconeManager::_spritesSymbole = nullptr;
/***************************************************/
/***************************************************/

void IconeManager::chargerMemoireIcones()
{
    cerr << endl
         << "chargerMemoireIcones" << endl;
    chargerTextures(cheminFichierTexturesRessources,
                    _texturesRessource, _spritesRessource, _nbRessources);
    chargerTextures(cheminFichierTexturesSymboles,
                    _texturesSymbole, _spritesSymbole, _nbSymboles);

    if (_nbRessources != NB_RESSOURCES ||
        _nbSymboles != NB_SYMBOLES)
    {
        std::cerr << _nbRessources << " / " << NB_RESSOURCES << " type de ressources" << std::endl
                  << _nbSymboles << " / " << NB_SYMBOLES << " symboles" << std::endl;
    }

    Vector2u textureSize = _spritesSymbole->getTexture()->getSize();

    _zoomTexture.top = 0;
    _zoomTexture.left = 0;
    _zoomTexture.width = textureSize.x / _nbSymboles;
    _zoomTexture.height = textureSize.y;

    _spritesRessource->setTextureRect(_zoomTexture);
    _spritesSymbole->setTextureRect(_zoomTexture);
}

void IconeManager::dechargerMemoireIcones()
{
    cerr << endl
         << "dechargerMemoireIcones" << endl;
    delete _spritesRessource->getTexture();
    delete _spritesRessource;
    delete _spritesSymbole->getTexture();
    delete _spritesSymbole;
}

void IconeManager::chargerTextures(string fichierCheminsTexture,
                                   Texture *&texture,
                                   Sprite *&spritesTab,
                                   uint &quantiteIcone)
{
    string cheminTexture;
    sf::Texture *textureTmp = nullptr;
    Sprite *sprite = nullptr;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        monFlux >> quantiteIcone;

        cerr << "Quantite d'icone : " << quantiteIcone << endl;

        cerr << "Chargement des textures et sprites d'une partie des icones" << endl;

        // Chemin de l'image texture des textures
        monFlux >> cheminTexture;
        cerr << cheminTexture << endl;

        // Create de la nouvelle texture
        textureTmp = new Texture();
        textureTmp->loadFromFile(cheminTexture);

        texture = textureTmp;
        spritesTab = new Sprite{*texture};

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/***************************************************/
/***************************************************/

void IconeManager::dessiner(TYPE_RESSOURCE typeRess,
                            const Vector2f &pos,
                            const Vector2f &scale)
{
    // Choisit la texture associée à la ressource
    _zoomTexture.left = (short)typeRess * _zoomTexture.width;
    // Place le Sprite sur dans l'écran
    _spritesRessource->setPosition(pos);
    // Definit la taille/scale du sprite
    _spritesRessource->setScale(scale);

    contextGlobal->dessinerFenetre(_spritesRessource);
}

void IconeManager::dessiner(SYMBOLE symbole,
                            const Vector2f &pos,
                            const Vector2f &scale)
{
    // Choisit la texture associée à la ressource
    _zoomTexture.left = (short)symbole * _zoomTexture.width;
    // Place le Sprite sur dans l'écran
    _spritesSymbole->setPosition(pos);
    // Definit la taille/scale du sprite
    _spritesSymbole->setScale(scale);

    contextGlobal->dessinerFenetre(_spritesSymbole);
}
