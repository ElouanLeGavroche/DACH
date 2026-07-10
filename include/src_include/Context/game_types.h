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
 * @brief strucutre qui regroupe les informations d'une image côté CPU
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
 * @brief strucutre qui regroupe les informations d'une image côté GPU
 * @param width largeur de l'image
 * @param height hauteur de l'image
 * @param nr_channels
 * @param path chemin de l'image 
 * @param data données de l'image
 */
typedef struct st_texture
{
    unsigned int id;
    unsigned char *data;
    int widht;
    int height;
}st_texture;

/**
 * @brief Structure qui stock le contenu d'un shader
 * @param shader id du shader
 */
typedef struct st_shader
{
    unsigned int shader;
} st_shader;

/**
 * @brief La structure qui permet de stocker un élément 3D
 * @param vertex_count le nombre de vertrices dans le modèle
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
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

}st_mesh;

typedef struct st_mesh_data
{
    unsigned int vertex_count;
    unsigned int index_count;

    float *vert_pos;
    int *face_indice;

}st_mesh_data;


typedef struct st_vec3
{
    float x;
    float y;
    float z;
}st_vec3;

typedef struct st_transform
{
    st_vec3 position;
    st_vec3 rotation;
    st_vec3 transformation;
}st_transform;

typedef struct st_material
{
    st_shader shader;
    st_texture texture;
}st_material;

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
typedef struct st_render_object
{
    int id;

    st_mesh *mesh;
    st_material *material;
    st_transform transform;

    int visible;
}st_render_object;

typedef struct st_render_group
{
    int ID;
    e_render_group_type type;
    void *data;

    void (* init_group)(st_render_group *group);

    void (* add_element)(st_render_group *group);
    void (* remove_element)(st_render_group *group);
    st_render_object* (* get_element)(st_render_group *group);
    void (* remove_all_elements)(st_render_group *group);
    void (* delete_group)(st_render_group *group); 

}st_render_group;

typedef struct st_instance_data
{
    float model[16]
}st_instance_data;

typedef struct st_instanced
{
    st_instance_data *cpu_data;
    int count;
    int capacity;
    unsigned int vbo;

}st_instanced;

typedef struct st_mesh_group
{
    st_render_object *objects;
    int nb_objects;
    st_shader *shaders;
    int nb_shaders;

}st_mesh_group;

typedef struct st_instanced_mesh_group
{
    st_render_object *shared_render_object;
    st_instanced st_instanced;

}st_instanced_mesh_group;

#endif