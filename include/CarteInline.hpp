/**
 * @file CarteInline.hpp
 * @author Mathieu VDT (mathieu.detorcy@gmail.com)
 * @brief Méthode inline de la classe Carte
 * @version 0.1
 * @date 2022-06-09
 * 
 * @copyright Copyright (c) 2022
 */

// Methode inline
inline Vector2u Carte::getDimensionGrille() const { return Vector2u{_nbColonnesGrille, _nbLignesGrille}; }

inline uint Carte::getDimensionGrilleLigne() const { return _nbLignesGrille; }

inline uint Carte::getDimensionGrilleColonne() const { return _nbColonnesGrille; }

inline Vector2u Carte::getDimensionCarte() const { return Vector2u(_nbColonnesCarte, _nbLignesCarte); }
inline uint Carte::getNbLignes() const { return _nbLignesCarte; }
inline uint Carte::getNbColonnes() const { return _nbLignesCarte; }

inline Vector2u Carte::getCoordCase(uint i, uint j) const
{
    return Vector2u(2 * j + (1 - (i % 2)), i / 2);
}

// Convertisseur coordonnées
inline Vector2u Carte::matriceToCarte(const Vector2u &cMat)
{

    uint xc = 2 * cMat.x + 1 - (cMat.y % 2);
    uint yc = cMat.y / 2;
    return Vector2u(xc, yc);
}
inline Vector2u Carte::carteToMatrice(const Vector2u &cCarte)
{
    uint xm = cCarte.x / 2;
    uint ym = 2 * cCarte.y + 1 - (cCarte.x % 2);
    return Vector2u(xm, ym);
}

inline Vector2u Carte::positionEcranToCarte(const Vector2f &)
{
    uint xCarte = 0;
    uint yCarte = 0;
    return Vector2u(xCarte, yCarte);
}

inline Vector2u Carte::matriceToPositionEcran(const Vector2u &)
{
    return Vector2u();
}
inline Vector2u Carte::positionEcranToMatrice(const Vector2u &)
{
    return Vector2u();
}
