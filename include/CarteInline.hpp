
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

inline Vector2f Carte::carteToPositionEcran(const Vector2u &cCarte)
{
    // float tailleCaseMap = CaseMap::getTailleCaseMap();
    float tailleCaseMap = CaseMap::getTailleCaseMap();
    float xEcran = 0.f;
    float yEcran = 0.f;
    // Décalage 1 ligen sur deux
    xEcran += (float)(cCarte.x % 2) * 0.75f * tailleCaseMap;
    // Décalage pour former la ligne
    // xEcran += ((float)cCarte.x - (float)(cCarte.x % 2)) * tailleCaseMap * 0.75f; // Equivalent à la ligne du dessous
    xEcran += (float)((int)(cCarte.x / 2)) * tailleCaseMap * 1.5f;

    // Décalage pour faire la demi interligne ...
    yEcran += (float)(1 - cCarte.x % 2) * tailleCaseMap / 2.f;
    // Décalage pour faire les lignes
    yEcran += (float)cCarte.y * tailleCaseMap;

    // printf("(%5d,%5d) et (%5f,%5f)\n\n", cCarte.x, cCarte.y, xEcran, yEcran);

    return Vector2f(xEcran, yEcran);
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
