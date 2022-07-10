Fichier expliquant comment réaliser les textures des Pipelines. 

Il y a 7 *[pour l'instant]* planches de textures différentes. (une par type de *pipeline*) 

Il y a *[pour l'instant]* 3 niveaux d'amélioration pour les pipelines. *(Hors pipelines non totalement connectés)*

La taille d'une case texture d'un pipeline doit être la même que celle des CaseMap *(ou des Structures)*. Elle est calculée sur la hauteur de la planche de Texture / 3. *(3 cases pipelines sur la hauteur par planche, 3 levels)*

--- 

## Enum sur les Textures des Pipelines
Enum utilisés pour gérer les offsets sur les Textures des Pipelines.
```cpp
// Type de Pipeline
enum TEXTURE
{
    NON_CONNECTE = 0,
    ALL_SORTIE = 1,
    ENTREE_ALL = 2,
    DROIT_VERTICAL = 3,
    ANGLE_LARGE = 4,
    DROIT_OBLIQUE = 5,
    ANGLE_ETROIT = 6,
    NB_TEXTURE = 7
};
```

```cpp
// Variant de Pipeline
enum OFFSET_TEXTURE
{
    // NON_CONNECTE
    A_A = 0,
    // ALL_SORTIE
    A_N = 0,
    A_NO = 1,
    A_SO = 2,
    A_S = 3,
    A_SE = 4,
    A_NE = 5,
    // ENTREE_ALL
    S_A = 0,
    SE_A = 1,
    NE_A = 2,
    N_A = 3,
    NO_A = 4,
    SO_A = 5,
    // DROIT_VERTICAL
    S_N = 0,
    N_S = 1,
    // ANGLE_LARGE
    S_NO = 0,
    S_NE = 1,
    N_SO = 2,
    N_SE = 3,
    NO_S = 4,
    NE_S = 5,
    SO_N = 6,
    SE_N = 7,
    NO_NE = 8,
    NE_NO = 9,
    SO_SE = 10,
    SE_SO = 11,
    // DROIT_OBLIQUE
    SE_NO = 0,
    NO_SE = 1,
    SO_NE = 2,
    NE_SO = 3,
    // ANGLE_ETROIT
    S_SO = 0,
    S_SE = 1,
    N_NO = 2,
    N_NE = 3,
    SO_S = 4,
    SE_S = 5,
    NO_N = 6,
    NE_N = 7,
    SO_NO = 8,
    NO_SE = 9,
    SE_NE = 10,
    NE_SE = 11,
};
```

---

## Une image par type de Pipeline suivant cette structure :  

|  Variant 0   |  Variant 1   |  Variant 2   |  Variant X   |
| :----------: | :----------: | :----------: | :----------: |
|   T0-V0-L0   |   T0-V1-L0   |   T0-V2-L0   |   T0-VX-L0   |
| **T0-V0-L1** | **T0-V1-L1** | **T0-V2-L1** | **T0-VX-L1** |
|   T0-V0-L2   |   T0-V1-L2   |   T0-V2-L2   |   T0-VX-L2   |

**Légende :**  
>  T => Type de Pipeline  [0-7]  
>  L => Level [0-2]  
>  V => Variant de Pipeline [0-5]  



