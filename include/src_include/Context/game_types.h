#ifndef GAME_TYPES
#define GAMEE_TYPES

#include "../../types.h"
/**
 * @brief ici le développeur doit indiqué TOUT les context de son jeu.
 * En sachant que le premier sera celui qui sera charger... En premier.
 */

/**
 * @brief strucutre qui regroupe les informations d'une image
 * @param width largeur de l'image
 * @param height hauteur de l'image
 * @param nr_channels
 * @param path chemin de l'image 
 * @param data données de l'image
 */
typedef struct
{
    int width;
    int height;
    int nr_channels;

    const char *path;
    unsigned char *data;
}st_image;

/**
 * @brief La structure qui permet de stocker un élément 3D
 * @param vertex_float_count le nombre de vertrices dans le modèle
 * @param index_count le nombre de face dans le modèle
 * @param vert_pos la position de ecs vertrices
 * @param face_indice l'ordre dans lequel il faut former les face avec les vertrices
 * @param VAO valeur des sommets à envoyé à la carte graphique
 * @param VBO buffer de sommets
 * @param EBO buffer de sommets
 * @param texture image de l'élément
 */
typedef struct
{
    int vertex_float_count;
    int index_count;

    float *vert_pos;
    int *face_indice;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int texture_id;

}st_mesh;


#ifndef context_list
#define context_list
typedef enum e_context_list{
    C_NONE,
    C_BACK,

    C_MAIN_MENU,
    C_GAME,

    C_NUM
} e_context_list;
#endif

extern st_state main_menu_state;
extern st_state game_state;


typedef struct{
    st_mesh mesh_obj;
    int x_pos;
    int y_pos;
    int z_pos;
}st_world_obj;

typedef struct{
    st_world_obj *world_obj;
}st_all_word_obj;

#endif