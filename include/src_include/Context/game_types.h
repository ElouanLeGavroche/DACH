#ifndef GAME_TYPES
#define GAME_TYPES

/**
 * @brief ici le développeur doit indiqué TOUT les context de son jeu.
 * En sachant que le premier sera celui qui sera charger... En premier.
 */
typedef enum e_context_list{
    C_NONE,
    C_BACK,

    C_MAIN_MENU,
    C_GAME,

    C_NUM
} e_context_list;


typedef enum e_render_group_type
{
    RENDER_GROUP_MESH,
    RENDER_GROUP_INSTANCED_MESH
} e_render_group_type;

/**
 * @brief strucutre qui regroupe les informations d'une image
 * @param width largeur de l'image
 * @param height hauteur de l'image
 * @param nr_channels
 * @param path chemin de l'image 
 * @param data données de l'image
 */
typedef struct st_image
{
    int width;
    int height;
    int nr_channels;

    const char *path;
    unsigned char *data;
}st_image;

/**
 * @brief Structure qui stock le contenu d'un shader
 * @param shader id du shader
 * @param set_int_uniform permet de faire passer une valeur entier dans le shader de la CG 
 * @param set_float_uniform permet de faire passer une valeur flotante dans le shader de la CG
 * @param set_bool_uniform permet de faire passer une valeur booleenne dans le shader de la CG
 */
typedef struct st_shader st_shader;
struct st_shader
{
    unsigned int shader;

    void(* set_int_uniform)(struct st_shader shader);
    void(* set_float_uniform)(struct st_shader shader);
    void(* set_bool_uniform)(struct st_shader shader);
    void(* use)(struct st_shader shader);

};

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
typedef struct st_mesh
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

/**
 * @brief Un object quelquonce du monde
 * 
 * @param ID l'id du groupe
 * @param mesh_obj le mesh lié à l'élément
 * @param x_pos position en x dans le monde
 * @param y_pos position en y dans le monde
 * @param y_pos position en z dans le monde
 * @param texture la texture coté CPU lié à l'objet (pas forcément pertinent, on verra après)
 * @param texture_id l'id de la texture côté GPU
 */
typedef struct st_world_obj
{
    int ID;

    st_mesh mesh_obj;
    float x_pos;
    float y_pos;
    float z_pos;

    st_image texture;
    unsigned int texture_id;
}st_world_obj;

/**
 * @brief liste des objet se trouvant dans un group
 * ils partagerons alors certaine infos, pour simplifier le rendu et rendre le tout plus lisible.
 * 
 * @param instencied si le groupe instensie ces éléments 
 * @param data liste des objets du groupe
 * @param shaders liste des shaders du groupe
 * @param all_matrices matrice des éléments qui seront envoyé en groupe au GPU
 */
/*
typedef struct st_render_group
{
    int ID;
    bool instencied;

    int nb_object;
    int nb_shader;
    
    st_shader *shaders;

    void *data;

}st_render_group;
*/
typedef struct st_render_group
{
    int ID;
    e_render_group_type type;
    void *data;

}st_render_group;


typedef struct st_mesh_group
{
    st_world_obj *objects;
    int nb_objects;
    st_shader *shaders;
    int nb_shaders;

}st_mesh_group;

typedef struct st_instanced_mesh_group
{
    st_mesh shared_mesh;
    int shared_texture;
    st_shader shared_shader;

    mat4 *instances;
    mat4 *instances_vbo;

}st_instanced_mesh_group;

#endif