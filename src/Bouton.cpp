/**
 * @file Bouton.cpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Implémentation des méthodes de la classe Bouton
 *
 * @version 0.1
 * @date 2022-08-31
 *
 * @copyright Copyright (c) 2022
 */
#include "Bouton.hpp"

string cheminFichierTexturesBoutons = "";

Texture *Bouton::_texturesBoutons[NB_BOUTONS];
// uint Bouton::_largeurBouton = 0; // Largeur d'1 Bouton
// uint Bouton::_hauteurBouton = 0; // Hauteur d'1 Bouton

Bouton::Bouton(/* args */)
{
}

Bouton::~Bouton()
{
}

/*******************************************************/
/*******************************************************/

void Bouton::chargerMemoireBoutons()
{
    cerr << endl
         << "chargerMemoireBoutons" << endl;
    chargerTextures(cheminFichierTexturesBoutons);

    // _largeurBouton = _texturesBoutons[0]->getSize().x;
    // _hauteurBouton = _texturesBoutons[0]->getSize().y / NB_STATE_BOUTONS;
}

void Bouton::dechargerMemoireBoutons()
{
    cerr << endl
         << "dechargerMemoireBoutons" << endl;
    for (int i = 0; i < NB_RESSOURCES; ++i)
    {
        delete _texturesBoutons[i];
    }
}

/**
 * @brief Charge les textures des différentes boutons en mémoire dans une variable static *(à partir d'un fichier indiquant les chemins)*
 *
 * @param string - *fichierCheminsTexture*
 */
void Bouton::chargerTextures(string fichierCheminsTexture)
{
    string nomFichierTexture[NB_RESSOURCES];
    string cheminTexture;
    sf::Texture *texture;

    ifstream monFlux;
    monFlux.open(fichierCheminsTexture);

    if (monFlux)
    {
        cerr << "Chargement des textures des Boutons" << endl;
        // Récupération des chemins
        for (int k = 0; k < NB_BOUTONS; ++k)
        {
            // Chemin de l'image texture d'une mine
            monFlux >> cheminTexture;
            cerr << cheminTexture << endl;

            // Create de la nouvelle texture
            texture = new Texture();
            texture->loadFromFile(cheminTexture);

            _texturesBoutons[k] = texture;
        }

        monFlux.close();
    }
    else
    {
        std::cerr << "/!\\ Erreur d'ouverture du fichier : " << fichierCheminsTexture << " /!\\" << endl;
    }
}

/*******************************************************/
/*******************************************************/
