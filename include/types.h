#ifndef TYPES
#define TYPES

#include <stdbool.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>

#include "../extern_lib/cglm/cglm.h"
#include "../extern_lib/cglm/types.h"

#include "src_include/Context/game_types.h"
#include "src_include/Config/constantes.h"

typedef struct st_engine st_engine;
typedef struct st_context st_context;


/**
 * @brief simple structure pour save deux entier dans une seule struct.
 * Permet de retourner des pos x et y dans un foncion.
 */
typedef struct tuple_int_duo
{
    int a;
    int b;
}tuple_int_duo;

/* Gestion des structures pour les inputs */

// Tableau qui contient tout les touches utilisable par le jeu
// Note : Si on veux mapper les touchent, ça va être compliqué avec ce système... à voir, à voir...
typedef enum e_key
{
    KEY_ESCAPE,
    KEY_UP,
    KEY_DOWN,
    KEY_ENTER,

    // Caméra
    KEY_Z,
    KEY_Q,
    KEY_S,
    KEY_D,
    KEY_A,
    KEY_E,

    KEY_NUM
}e_key;

typedef enum e_mouse
{
    MOUSE_SCROLL_Y,
    MOUSE_NUM
}e_mouse;

// Savoir quand une touche est pressé ou relacher( permet de géré des entrer du type CTRL+C)
typedef struct
{
    // Quand une touche est enfoncée
    bool down[KEY_NUM];
    // Quand une touche est appuyer momentanément
    bool pressed[KEY_NUM];
    // Quand une touche est lachée
    bool release[KEY_NUM];

}st_input;

/**
 * @brief Structure de la souris
 */
typedef struct
{
    double scroll_y;
    bool active_scroll_y;

    double scroll_x;
    bool active_scroll_x;

}st_mouse;


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
typedef struct st_camera st_camera;
struct st_camera{
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

    float rotation;

    // Cette variables sert à savoir lorsque qu'il faut effectuer une rotation et quand elle est fini
    float target;

    void (*look)(st_camera *camera);
    void (*camera_speed)(st_camera *camera, float delta_time);
    void (*update_ortho)(st_camera *camera);
};

// Permet de savoir vers quelle direction va la caméra
typedef enum e_dir{
    UP,
    LEFT,
    DOWN,
    RIGHT,
    ROTATE_L,
    ROTATE_R
}e_dir;

/**
 * @brief Structure qui stock les informations de rendu du context
 * @param VAOs Liste des sommets
 * @param VBOs Liste Buffer
 * @param EBOs Liste Buffer
 * @param shader_programs Liste des programe shaders
 * @param camera structure de données de la camera
 */
typedef struct st_render_data{

    st_render_group *groups;
    int nb_groups;
    int nb_total_groups;

    st_camera camera;

}st_render_data;

/**
 * @brief ici le développeur doit indiqué TOUT les context de son jeu.
 * En sachant que le premier sera celui qui sera charger... En premier.
 */
typedef enum e_context_list{
    C_NONE,
    C_BACK,

    C_MAIN_MENU,
    C_GAME,
    C_PAUSE_MENU,

    C_NUM
} e_context_list;

typedef enum
{
    CONTEXT_ACTION_NONE, // Rien
    CONTEXT_ACTION_PUSH, // On met en avant
    CONTEXT_ACTION_POP, // On retire
    CONTEXT_ACTION_REPLACE, // On remplace
    CONTEXT_ACTION_QUIT // On quitte
}e_context_actions;

typedef struct st_context_request
{
    e_context_actions action;
    e_context_list target;
}st_context_request;


/**
 * @brief Cette structure est TRÈS importante... En effet, elle permet de dire si un context va afficher, actualiser ou géré les inputs
 * de son parent. Il est d'ailleurs recursrive : La pause affiche simplement son parent, qui est l'UI et lui affiche, gère les input, et actualise
 * son parent qui est le jeu, mais il ne peux pas l'actualiser, car la pause lui block l'actualisation.
 * 
 * @param render_bellow rendre le parent
 * @param input_bellow prendre en compte les entrées du parent
 * @param update_bellow met à jour la logique du parent
 */
typedef struct st_context_politicy
{
    bool render_bellow;
    bool input_bellow;
    bool update_bellow;
}st_context_politicy;

/**
 * @brief Structure (presque class) qui contient deux catégorie d'élément
 * 
 * 1 - Des pointeurs de fonction, celle-ci servent à y placer de manière efficaces toutes les page de l'application
 * sans devoir appeler des fonction à des endroit différente tout le temps.
 * 
 * 2 - Un pointeur vers (s'il y en à un) un parent. Ex : je suis sur le menu pause, le parent est le jeu) 
 * 
 * @param id permet de savoir de quelle context il s'agit aisémment
 * @param st_context fonction qui initialisera la fenêtre.
 * @param update_logic_context fonction qui déroulera à chaque tick la logique du canva.
 * @param update_render_context fonction qui déroulera le rendu à chaque frame le rendu de la page.
 * @param inputs structure des entrées clavier.
 * @param mouse structure des déplacements de la souris
 * @param render données de rendu du context.
 * @param request gère les requête du context 
*/
typedef struct st_context
{
    // l'id du context
    int id;

    // L'initialiseur connait tout
    int (*init_state)(st_context *state);
    // La logique ne connaitra que les model
    void (*update_logic_context)(st_context *state);
    // Le rendu ne connait que les données liée au rendu
    void (*update_render_context)(st_render_data *render, double time);

    // Structure sépcifique à un context
    void *model;

    // Permet de stocker les inputs qui gérerons les actions en conséquent
    st_input inputs;
    // Permet de stocker les mouvement de la souris et de les traiter
    st_mouse mouse;
    // Permet de stocker les information de rendu
    st_render_data render;

    st_context_politicy politicy;

    st_context_request request;
}st_context;


/**
 * @brief   Le stack permet de hierachisé l'ordre d'apparition des page.
 * 
 * Si on et le jeu en pause, le canva pause prend le dessus sur le jeu, et quand on la quitte, le jeu reprend.
 * 
 * @param stack_context La stack au global
 * @param current_context Le context actuellement en tête de la stack
 * @param level_of_depth Niveau de profondeur de la state.
 */
typedef struct {
    st_context *stack_context[MAX_CONTEXT];
    st_context *current_context;
    int level_of_depth;
}st_stack;

/**
 * @brief table qui sert à géré les context.
 * 
 * @param push_context Pousse le context dans la stack
 * @param exit_context Retire le context de la stack
 * @param pause_context met en pause un context - lorsqu'un context est ajouter par dessus
 * @param resume_context réveil de ça pause une context - lorsque l'on revient sur lui
 * @param destroy_context supprime un context - supprime la structure
 */
typedef struct
{
    int (*create_context) (st_context *state);
    int (*replace_context) (st_context *new_context, st_stack *stack);
    int (*push_context) (st_context *new_context, st_stack *stack);
    int (*exit_context)(st_stack *stack);
    
}vt_context_tool;

// Structure pour la taille et le frame rate du contexte OpenGL
typedef struct {
    int size_x;
    int size_y;

    float frame_rate;
}st_loaded_windows_data;

typedef st_context *(*dict_register)(void);

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
 * @param st_loaded_windows_data les informations de la fenêtre
 * @param dict_register la liste des context du jeu sous forme d'un dictionnaire pour avoir accès à leur initialisateur
 * @param dt_time le temps du jeu
 */
typedef struct st_engine
{
    // éléments général
    atomic_bool running;
    
    // élément liées au context et à la stack
    st_stack stack_context;
    vt_context_tool context_tool;

    st_loaded_windows_data window;

    dict_register all_contexts[C_NUM];

    double dt_time;
    
} st_engine;

// Structure qui englobe les éléments qui ont besoin d'être envoyé à la fenêtre
typedef struct
{
    st_camera *camera;
    st_input *input;
    st_mouse *mouse;

    st_loaded_windows_data *window;
}st_window_user_data;

#endif