#ifndef TYPE
#define TYPE

#include <stdbool.h>
#include <stdatomic.h>

//#include <GLFW/glfw3.h>

// Les chaine
typedef char t_letter;

typedef struct
{
    int length;
    int max_length;
    t_letter l;
    t_letter *next; 
}st_string;

/**
 * @brief Structure (presque class) qui contient deux catégorie d'élément
 * 
 * 1 - Des pointeurs de fonction, celle-ci servent à y placer de manière efficaces toutes les page de l'application
 * sans devoir appeler des fonction à des endroit différente tout le temps.
 * 
 * 2 - Un pointeur vers (s'il y en à un) un parent. Ex : je suis sur le menu pause, le parent est le jeu) 
 * 
 * @param state fonction qui initialisera la fenêtre
 * @param input_context fonction qui donne le context de que font tel ou tel touches
 * @param update_logic_context fonction qui déroulera à chaque tick la logique du canva
 * @param update_render_context fonction qui déroulera le rendu à chaque frame le rendu de la page
 */
typedef struct state
{
    void (*state)();

    void (*input_context)();
    void (*update_logic_context)();
    void (*update_render_context)();
    
    struct state *upper;
}state;

/**
 * @brief   Le stack permet de hierachisé l'ordre d'apparition des page.
 * 
 * Si on et le jeu en pause, le canva pause prend le dessus sur le jeu, et quand on la quitte, le jeu reprend.
 * 
 * @param state Est une structure simple. Pour en savoir plus, cliquer dessus.
 */
typedef struct {
    state *current_state;
}stack;

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
    stack stack_context;
}st_engine;


// Structure pour la taille et le frame rate du contexte OpenGL
typedef struct {
    int size_x;
    int size_y;
    float frame_rate;
}st_loaded_windows_data;


#endif