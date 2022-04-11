Fichier expliquant comment réaliser les textures des Mines. 

Il y a 5 *[pour l'instant]* mines différentes. (une par ressource *matière première*) 

Il y a *[pour l'instant]* 4 frames d'animations pour les différentes mines.

Il y a *[pour l'instant]* 3 niveaux d'amélioration pour les mines.

La taille d'une case texture d'une mine doit être la même que celle des CaseMap. 

```cpp
    // Matières premières
    PoussiereRegolite,
    MineraiGlace,
    MineraiTitane,
    MineraiSilicium,
    MineraiFer,
```

---

## Une image par type de Mine suivant cette structure :  


|   Frame 0    |   Frame 1    |   Frame 2    |   Frame 3    |
| :----------: | :----------: | :----------: | :----------: |
|   M0-L0   |   M0-L0   |   M0-L0   |   M0-L0   |
| **M0-L1** | **M0-L1** | **M0-L1** | **M0-L1** |
|   M0-L2   |   M0-L2   |   M0-L2   |   M0-L2   |

**Légende :**  
>  M => Mine  [0-4]  
>  L => Level [0-2]  
>  F => Frame [0-3]  



