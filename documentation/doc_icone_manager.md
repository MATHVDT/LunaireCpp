# Documentation classe IconeManager
Fichier expliquant le fonctionnement de la classe *IconeManager*.

Cette classe sert à gerer toutes les icones du jeu.
Il y a *[pour l'instant]* 2 types d'icones : 
* ressources
* symboles

## Icone ressources
Les icones ressources servent à afficher les crafts et formule de craft dans le menu.

### Charger la textures des icones ressources
La classe possède un sprite et une texture associées aux ressources. 
Pour charger cette texture, il suffit de fournir le chemin du fichier contenant le chemin de l'image associée dans la variable *string cheminFichierTexturesRessources*. Le fichier s'agence de cette façon :
```txt
X
chemin_image
```
* *X* correspond au nombre de type de ressources différentes (TYPE_RESSOURCE::RIEN inclu) 
* *chemin_image* correspond au chemin relatif de l'image servant de texture pour les ressources

### Description de l'image icone ressources
Sur cette image, tous les textures des différents types de ressources sont présent sur une seule ligne. Chaque texture de ressource correspond à un carré de 100x100 pixel *[pour l'instant, peut être si on change ca casse tout]*.

### Choix de la texture de la ressource 
Grâce à la méthode `static const Texture *getTexturesRessource();` on obtient la texture qui contient sur une ligne tout les icones des ressources. On charge cette texture dans un objet SFML *Drawable* (ici de préférence un *RectShape*).
Pour obtenir l'icone du ressource en particulier, il faut utiliser l'*enum TYPE_RESSOURCE* présent dans le fichier *EnumTypeRessource.hpp*. Cette enum permet d'avoir l'index de la ressource souhaité dans la texture chargée. Pour zoomer ensuite dessus, il faut récupérer le rectangle de zoom via la méthode `static IntRect &getZoomTextureRessource(TYPE_RESSOURCE r);`. Une fois ce rectangle de zoom récupéré, on l'applique au *Drawable* via la méthode `setTextureRect(const IntRect & rect)`. Cela permet d'afficher juste l'icone de la ressource qui nous interesse.


## Icone symbole
Les icones symboles servent à afficher des flèches, plus, moins ou égale dans le menu.

### Charger la textures des icones symboles
La classe possède un sprite et une texture associées aux symboles. 
Pour charger cette texture, il suffit de fournir le chemin du fichier contenant le chemin de l'image associée dans la variable *string cheminFichierTexturesSymboles*. Le fichier s'agence de cette façon :
```txt
X
chemin_image
```
* *X* correspond au nombre de symboles différentes 
* *chemin_image* correspond au chemin relatif de l'image servant de texture pour les symboles

### Description de l'image icone symbole
Sur cette image, tous les textures des différents symboles sont présent sur une seule ligne. Chaque texture de symbole correspond à un carré de 100x100 pixel *[pour l'instant, peut être si on change ca casse tout]*.

### Choix de la texture du symbole
Grâce à la méthode `static const Texture *getTexturesSymbole();` on obtient la texture qui contient sur une ligne tout les icones des symboles. On charge cette texture dans un objet SFML *Drawable* (ici de préférence un *RectShape*).
Pour obtenir l'icone du symbole en particulier, il faut utiliser l'*enum SYMBOLE* présent dans le fichier *EnumTypeSymbole.hpp*. Cette enum permet d'avoir l'index de la symbole souhaité dans la texture chargée. Pour zoomer ensuite dessus, il faut récupérer le rectangle de zoom via la méthode `static IntRect &getZoomTextureSymbole(SYMBOLE s);`. Une fois ce rectangle de zoom récupéré, on l'applique au *Drawable* via la méthode `setTextureRect(const IntRect & rect)`. Cela permet d'afficher juste l'icone de la symbole qui nous interesse.