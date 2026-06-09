# Présentation
Après plusieurs mois sans rien faire, je me relance dans le développement de ce jeu. En effet, je suis las de ne plus coder, et je ressens un certain besoin de profiter à nouveau des bonheurs du debug.

#### Pourquoi ?

Tout simplement car je suis un peu obligé d'utiliser l'IA dans mon travail actuel et que je n'aime pas ça. J'ai donc besoin de me retrouver le soir devant mon PC et aucun agent qui m'aide à faire ce que je veux comprendre par moi-même.

#### Où cela va me mener ?

Je ne sais pas, on verra où me mène ce jeu, je code à mon rythme pour passer mon temps car je me fais chier.

#### Hag e brezhonneg ?

Ma on kab skrivañ ar yezh.


*ken ar c'hentañ*


# Règles du développement du projet

## Normalisation des fichiers
- Separateur **;**
- Case **snake_case**

# Manuel 

## Librairies extern à installer
Vous devez en premier lieux installer GLFW.

```bash
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
```

Puis télécharger via se site GLAD
https://glad.dav1d.de/

Mettez-y les options :
#### Language
- C/C++

#### Specification
- OpenGL

#### Profile
- Core

Puis généré le document.

Par la suite, vous devrez copie glad/glad.h et KHR/khrplatform.h dans le dossier usr/lib
```bash
sudo cp -r ~/Téléchargements/glad/include/glad ~/usr/lib/
sudo cp -r ~/Téléchargements/glad/include/KHR ~/usr/lib/
```
## Exec
make && make clean | ./out/DACH 


# MVC
Le MVC que j'utilise prend 2 formes :
- La première est la plus basique : on envoie des infos au contrôleur, ça va dans le modèle, puis c'est affiché sur l'écran de la vue.
    Ex : 
    ```c
    void main_controller():
        int data = calcul_model();
        rendu_view(data);
    ```
- Le second sont pour les outils qui ne touchent pas à l'affichage : on envoie des infos au contrôleur qui les envoie au modèle, puis à la view qui va mettre en forme ces informations avant de les renvoyer à nouveau au contrôleur qui va les retourner.
    Ex :
    ```c
    void main_controller():
        int data = calcul_model();
        int data_en_page = rendu_view(data);
        
        return data_en_page;
    ```

*Note : *
Certains outils sont suffisamment simples pour n'être présents que sous la forme d'une fonction à appeler.
Je pense notamment à l'outil de couleurs.