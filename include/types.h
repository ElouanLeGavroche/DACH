#ifndef TYPES
#define TYPES

#include <stdbool.h>
#include <stdlib.h>
#include <stdatomic.h>

#include <cglm/cglm.h>
#include <cglm/types.h>

typedef struct st_engine st_engine;
typedef struct st_state st_state;

//////////////////
//              //
//  ENTIER      //
//  NON SIGNÉ   //
//              //
//////////////////

// Structure pour faire une liste chainée d'entier non signée
typedef struct st_unsigned_int st_unsigned_int;


// Structure d'un entier non signée d'une liste
// Il sert uniquement pour stocker les éléments 3D
struct st_unsigned_int
{
    unsigned int value;
    st_unsigned_int *next;

    int nb_face;
    int nb_vert;
};


// Structure de la liste d'entier non signée
typedef struct{
    st_unsigned_int *first;
    int size;
} st_unsigned_int_list;

//structures qui regroupent tout les meshs et les shader
typedef struct st_mesh st_mesh;

struct st_mesh
{
    int nb_vert;
    int nb_face;
    float *vert_pos;
    int *face_pos;

};

// Le bool "one of them" sert à verifier s'il y en a
// au moins un d'actionner. Pour éviter de parcourir
// un switch pour rien.
typedef struct
{
    atomic_bool escape;
    atomic_bool up_arrow;
    atomic_bool down_arrow;
    atomic_bool enter;
    atomic_bool one_of_them;
}st_input;


/**
 * @brief Structure qui stock le contenu d'un shader
 */

typedef struct
{
    unsigned int shader;

    void(* set_int_uniform)();
    void(* set_flaot_uniform)();
    void(* set_bool_uniform)();

}st_shader;


/**
 * @brief Structure qui contient les informations de la caméra
 */
typedef struct{
    mat4 view_point;
}st_camera;

/**
 * @brief Structure qui stock les informations de rendu du context
 * @param VAOs Liste des sommets
 * @param VBOs Liste Buffer
 * @param EBOs Liste Buffer
 * @param shader_programs Liste des programe shaders
 * @param camera structure de données de la camera
 */
typedef struct{

    unsigned int nb_shader;

    st_unsigned_int_list *VAOs;
    st_unsigned_int_list *VBOs;
    st_unsigned_int_list *EBOs;


    st_shader *shader_programs;
    st_camera camera;

}st_render_data;

/**
 * @brief Structure (presque class) qui contient deux catégorie d'élément
 * 
 * 1 - Des pointeurs de fonction, celle-ci servent à y placer de manière efficaces toutes les page de l'application
 * sans devoir appeler des fonction à des endroit différente tout le temps.
 * 
 * 2 - Un pointeur vers (s'il y en à un) un parent. Ex : je suis sur le menu pause, le parent est le jeu) 
 * 
 * @param st_state fonction qui initialisera la fenêtre
 * @param input_context fonction qui donne le context de que font tel ou tel touches
 * @param update_logic_context fonction qui déroulera à chaque tick la logique du canva
 * @param update_render_context fonction qui déroulera le rendu à chaque frame le rendu de la page
 */
typedef struct st_state
{
    // L'initialiseur connait tout
    void (*init_state)(st_state *state);
    // L'input ne connait que les entrée clavier
    int (*input_context)(st_input *inputs);
    // La logique ne connaitra que les model
    void (*update_logic_context)(st_engine *engine_state);
    // Le rendu ne connait que les données liée au rendu
    void (*update_render_context)(st_render_data *render);
    
    struct st_state *upper;
    st_render_data render;
    
}st_state;
/**
 * @brief   Le stack permet de hierachisé l'ordre d'apparition des page.
 * 
 * Si on et le jeu en pause, le canva pause prend le dessus sur le jeu, et quand on la quitte, le jeu reprend.
 * 
 * @param st_state Est une structure simple. Pour en savoir plus, cliquer dessus.
 */
typedef struct {
    st_state *current_state;

    atomic_int level_of_depth;
}stack;

/**
 * @brief étant un outil très général au moteur et très important, je décide de l'intégré directement en-tant que structure de fonction.
 * 
 * En effet, vu que le changement d'écran peut-avoir lieux à autant d'endroit où l'on à l'écran, il sera plus simple d'y accédé directement
 * via st_engin...
 * 
 * @param put_context fonction pour ajouter à la stack un context donnée.
 * @param remove_context retire le dernier context ajouter (celui affiché) pour le remplacer par le précédent.
 *         : " Il bloque la suppression s'il n'y a pas de context précédent. "
 */
typedef struct
{
    void (*put_context) (stack *my_stack, st_state *my_state);
    int (*remove_context)(stack *my_stack);
    
}st_context_tool;

/**
 * @brief Structure du moteur.
 * 
 * NOTE IMPORTANTE /!\ - Le moteur n'a pas besoin de conaitre directement le contenu
 * des pages. En effet, un context possède des éléments, et ces élément des comportements :
 * graphique, logique ou statiques.
 * En bref, les informations propre au context sont stocké en eux-même.
 * 
 * A voir si je la split en plusieurs structure à l'avenir pour des question de lisibilité.
 * 
 * @param render Ici les information qui servent au rendu (les VBO, VAO...).
 */
typedef struct st_engine
{
    // éléments général
    atomic_bool running;
    st_input input;
    
    // élément liées au context et à la stack
    stack stack_context;
    st_context_tool context_tool;
    st_state *next_state;

} st_engine;


// Structure pour la taille et le frame rate du contexte OpenGL
typedef struct {
    int size_x;
    int size_y;
    float frame_rate;
}st_loaded_windows_data;

#endif