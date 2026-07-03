#ifndef TYPES
#define TYPES

#include <stdbool.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>

#include <cglm/cglm.h>
#include <cglm/types.h>

#include "src_include/Context/game_types.h"

typedef struct st_engine st_engine;
typedef struct st_state st_state;

// Gestion des structures pour les inputs

// Tableau qui contient tout les touches utilisable par le jeu
// Note : Si on veux mapper les touchent, ça va être compliqué avec ce système... à voir, à voir...
typedef enum e_key
{
    KEY_ESCAPE,
    KEY_UP,
    KEY_DOWN,

    // Caméra
    KEY_Z,
    KEY_Q,
    KEY_S,
    KEY_D,

    KEY_NUM
}e_key;

// Savoir quand une touche est pressé ou relacher( permet de géré des entrer du type CTRL+C)
typedef struct
{
    // Quand une touche est enfoncée
    bool down[KEY_NUM];
    // Quand une touche est appuyer momentanément
    bool pressed[KEY_NUM];
    // Quand une touche est lachée
    bool release[KEY_NUM];
    pthread_mutex_t mutex;
    // Permet de savoir si l'autre thread a lu les informations
    atomic_bool ok;

}st_input;

/**
 * @brief Structure qui contient les informations de la caméra
 * @param view ce que voit la caméra
 * @param projection le type de projection à appliquer (ortho, perspective...)
 * @param ratio le champ de vision de la caméra
 * @param pos la position de la caméra
 * @param front ce que regarde la caméra
 * @param up l'inclinaison de la caméra
 * @param speed la valeur absolu (inchangé au cours du code) de la vitesse de la caméra
 * @param actual_speed la valeur relative de la caméra en fonction de la vitesse de rendu du jeu
 * @param near_z au plus proche que va rendre la caméra
 * @param far_z au plus loin que va voir la caméré
 */
typedef struct{
    mat4 view;
    mat4 projection;

    float ratio;

    vec3 pos;
    vec3 front;
    vec3 up;

    float speed;
    float actual_speed;

    float near_z;
    float far_z;

    float ortho_size;

}st_camera;

// Permet de savoir vers quelle direction va la caméra
typedef enum e_dir{
    UP,
    LEFT,
    DOWN,
    RIGHT
}e_dir;

/**
 * @brief Structure qui stock les informations de rendu du context
 * @param VAOs Liste des sommets
 * @param VBOs Liste Buffer
 * @param EBOs Liste Buffer
 * @param shader_programs Liste des programe shaders
 * @param camera structure de données de la camera
 */
typedef struct{

    int nb_shader;
    int nb_mesh;

    st_mesh *meshs;
    st_shader *shader_programs;

    st_camera camera;

    // Variables qui me permettront de géré le déplacement de la caméra indépendamment de la clock
    float delta_time;
    float last_time;

}st_render_data;

/**
 * @brief Structure (presque class) qui contient deux catégorie d'élément
 * 
 * 1 - Des pointeurs de fonction, celle-ci servent à y placer de manière efficaces toutes les page de l'application
 * sans devoir appeler des fonction à des endroit différente tout le temps.
 * 
 * 2 - Un pointeur vers (s'il y en à un) un parent. Ex : je suis sur le menu pause, le parent est le jeu) 
 * 
 * @param id permet de savoir de quelle context il s'agit aisémment
 * @param st_state fonction qui initialisera la fenêtre.
 * @param update_logic_context fonction qui déroulera à chaque tick la logique du canva.
 * @param update_render_context fonction qui déroulera le rendu à chaque frame le rendu de la page.
 * @param inputs structure des entrée clavier.
 * @param upper sont parent s'il en à un.
 * @param render données de rendu du context.
 * @param ev_next_context variable qui sera lu par le moteur et qui passera à un état suivant.
 * @param ev_ev_close_close varibale qui sera lu par le moteur et qui quittera le jeu.
 */
typedef struct st_state
{
    // l'id du context
    atomic_int id;

    // L'initialiseur connait tout
    int (*init_state)(st_state *state);
    // La logique ne connaitra que les model
    void (*update_logic_context)(st_state *state);
    // Le rendu ne connait que les données liée au rendu
    void (*update_render_context)(st_render_data *render);

    // Permet de stocker les inputs qui gérerons les actions en conséquent
    st_input inputs;

    struct st_state *upper;
    st_render_data render;

    // Permet de savoir si un nouvel etat est attendu
    atomic_int ev_next_context;
    // Permet de savoir si on doit fermet le jeu
    atomic_bool ev_must_close;

    
}st_state;


/**
 * @brief   Le stack permet de hierachisé l'ordre d'apparition des page.
 * 
 * Si on et le jeu en pause, le canva pause prend le dessus sur le jeu, et quand on la quitte, le jeu reprend.
 * 
 * @param st_state Est une structure simple. Pour en savoir plus, cliquer dessus.
 * @param level_of_depth Niveau de profondeur de la state.
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

// Structure pour la taille et le frame rate du contexte OpenGL
typedef struct {
    int size_x;
    int size_y;

    float frame_rate;
}st_loaded_windows_data;

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
 * @param running pour savoir si le jeu tourne
 * @param stack_context structure des contexts du moteur
 * @param context_tool petite boite à outil pour géré les contexts
 */
typedef struct st_engine
{
    // éléments général
    atomic_bool running;
    
    // élément liées au context et à la stack
    stack stack_context;
    st_context_tool context_tool;

    st_loaded_windows_data window;
    
    pthread_mutex_t context_mutex;

} st_engine;

// Structure qui englobe les éléments qui ont besoin d'être envoyé à la fenêtre
typedef struct
{
    st_camera *camera;
    st_input *input;
    st_loaded_windows_data *window;
}st_window_user_data;

#endif