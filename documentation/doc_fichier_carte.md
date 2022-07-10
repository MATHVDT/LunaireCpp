Les deux premiers nombres correspondes aux dimensions de la **carte**.
> nb_colonnes nb_lignes

Les nombres suivant correspondent aux types de ressources associées à l'*enum classe Sol*.
```cpp
enum class Sol
{
    Vierge,
    Trou,
    Montage,
    GisementOr,
    GisementFer,
};
```
Cela correspond à la **matrice grille** de la carte. 
> 1 ligne dans la carte = 2 lignes dans la grille   
> 2 colonnes dans la carte = 1 colonne dans la grille  
