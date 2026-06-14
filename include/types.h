#ifndef TYPE
#define TYPE

#include <stdbool.h>
#include <stdatomic.h>

typedef struct st_engine st_engine;
typedef struct st_state st_state;

typedef struct st_unsigned_element st_unsigned_element;

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
    void (*init_state)(st_engine *engine_state);
    void (*input_context)(st_engine *engine_state);
    void (*update_logic_context)(st_engine *engine_state);
    void (*update_render_context)(st_engine *engine_state);
    
    struct st_state *upper;
    
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
    st_state *next_state;

    int level_of_depth;
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


/*
tile qui auron toujours le même nombre d'elts
à faire évoluer
*/
typedef struct st_points
{
    int used;
    float x[24];

}st_tile;



// Le bool "one of them" sert à verifier s'il y en a
// au moins un d'actionner. Pour éviter de parcourir
// un switch pour rien.
typedef struct
{
    bool escape;
    bool up_arrow;
    bool down_arrow;
    bool enter;

    bool one_of_them;
}st_input;


typedef struct st_unsigned_element{
    unsigned int elt;
    struct st_unsigned_element *next;
} st_unsigned_element;

/**
 * @brief Structure qui stock les informations de rendu du context
 */
typedef struct{
    st_unsigned_element VAOs;
    st_unsigned_element VBOs;
    st_unsigned_element EBOs;


    st_unsigned_element shader_programs;

    unsigned int render_mode;

}st_render_info;


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
 * @param render_info Ici les information qui servent au rendu (les VBO, VAO...).
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

    st_render_info render_info;

} st_engine;


// Structure pour la taille et le frame rate du contexte OpenGL
typedef struct {
    int size_x;
    int size_y;
    float frame_rate;
}st_loaded_windows_data;


#endif