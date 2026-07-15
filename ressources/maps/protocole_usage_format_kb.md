# Protocle de rédaction des fichiers KB
*Kb pour kartenn Bed, ou carte du monde en Breton*

Le moteur qu'embarque DACH fonction en cette manière :

Fenêtre -> Context -> Groupes -> Éléments -> Rendu.

Avec cette ordre en tête, une grande partie des objects se retrouvent par miliers dans des groupes avec les même texture, mesh, shader. C'est avec cela en tête qu'est réfléchit le système de fichier de carte KB.

Le protocole se défini en deux partie principale :
- La première est la définition des groupes :
    - Nom du groupe
    - parenthèse
    - prm0 identifiant unique
    - prm1 path vers l'objet
    - prm2 path vers le shader vertex
    - prm3 path vers le shader frag
    - prm4 path vers ça texture
    - fermeture de la parenthèse

- La seconde est les objects de ces groupe
    - identifiant du group
    - un objet
      - indice x
      - indice y
      - hauteur

*exemple en format KB*
```kb
TILE_1 
(
    0, 
    "ressources/tiles/tile.obj",
    "src/Shaders/main_shader.vert", 
    "src/Shaders/main_shader.frag",
    "ressources/images/grass_test.jpg"
);

TILE_2 
(
    1,
    "ressources/tiles/tile.obj",
    "src/Shaders/main_shader.vert", 
    "src/Shaders/main_shader.frag", 
    "ressources/images/grass_test.jpg"
);


0 (0.0, 0.0, 0),(1.0, 0.0, 1);
1 (1.0, 0.0, 0),(1.0, 1.0, 1);
```