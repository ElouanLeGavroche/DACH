# Présentation
Après plusieurs mois sans rien faire, je me relance dans le développement de ce jeu. En effet, je suis las de ne plus coder, et je ressent un certain besoin à profiter à nouveau des bonheur du debug.

#### Pourquoi ?

Tout simplement car je suis un peu obligé d'utiliser l'IA dans mon travail actuel et que je n'aime pas ça. J'ai donc besoin de me retrouver le soir devant mon pc et aucun agent qui m'aide à faire ce que je veux comprendre par moi même.

#### Où cela va me mené ?

Je ne sais pas, on verra ou me mène ce jeu, je code à mon rythme pour passer mon temps car je me fais chier.

#### Hag e brezhonneg ?

Ma on kab skrivañ ar yezh.


*ken ar c'hentañ*


# Règles du développement du projet

## Normalisation des fichiers
- Separateur **;**
- Case **snake_case**


# Exec
make && make clean | ./out/DACH 


# MVC
Le MVC Que j'utilise prend 2 formes :
- La premieère, est la plus basique : on envoie des infos au controller, ça va dans le model, puis c'est afficher sur l'écran de la view.
    Ex : 
    ```c
    void main_controller():
        int data = calcul_model();
        rendu_view(data);
    ```
- Le second sont pour les outils qui ne touchent pas à l'affichage : on envoie des infos au controller qui les envoie au model, puis à la view qui va mettre en formes ces information avant de les renvoyée à nouveau au controller qui va les retourner.
    Ex :
    ```c
    void main_controller():
        int data = calcul_model();
        int data_en_page = rendu_view(data);
        
        return data_en_page;
    ```

*Note : *
Certain outils sont suffisamment simple pour n'est présent que sous la forme d'une fonction à appeler.
Je pense notamment à l'outil de couleurs.