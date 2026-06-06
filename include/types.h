#ifndef TYPE
#define TYPE

#include <stdbool.h>
#include <stdatomic.h>

//#include <GLFW/glfw3.h>

// Les chaine
typedef char letter;

typedef struct
{
    int length;
    int max_length;
    letter l;
    letter *next; 
}string;

// Le bool "one of them" sert à verifier s'il y en a
// au moins un d'actionner. Pour éviter de parcourir
// un switch pour rien.
typedef struct
{
    bool escape;
    bool one_of_them;
}st_input;

typedef struct
{
    atomic_bool running;
    st_input input;
}st_engine;


// Structure de la fenêtre principale
typedef struct
{
    //GLFWwindow window;

    int size_x;
    int size_y;

    int frame_rate;

}st_view;

// Structure pour la taille et le frame rate du contexte OpenGL
typedef struct {
    int size_x;
    int size_y;
    float frame_rate;
}t_loaded_windows_data;

#endif