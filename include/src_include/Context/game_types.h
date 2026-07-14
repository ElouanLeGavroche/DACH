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
 * @param id identifiant de la texture
 * @param data information de la texture
 * @param width largeur de l'image
 * @param height hauteur de l'image
 */
typedef struct st_texture
{
    unsigned int id;
    int nb_occurences;
}st_texture;

/**
 * @brief Structure qui stock le contenu d'un shader
 * @param shader id du shader
 * @param nb_occurences Permet de savoir combien d'objet on ce shader avant de le free
 */
typedef struct st_shader
{
    unsigned int shader;
    int nb_occurences;
} st_shader;

/**
 * @brief La structure qui permet de stocker un élément 3D côté GPU
 * @param VAO valeur des sommets à envoyé à la carte graphique
 * @param VBO buffer de sommets
 * @param EBO buffer de sommets
 * @param nb_occurences Permet de savoir combien d'objet on ce mesh avant de le free
 */
typedef struct st_mesh
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int index_count;
    int nb_occurences;

}st_mesh;

/**
 * @brief information d'un mesh côté CPU
 * @param vertex_count le nombre de vertex
 * @param index_count le nombre de face total
 * @param vert_pos information sur les vertex(px, py, pz, cx, cy, cz, tx, ty, tz)
 * @param face_indice comment sont relier les vertex entre-eux (v1, v2, v3)
 */
typedef struct st_mesh_data
{
    unsigned int vertex_count;
    unsigned int index_count;

    float *vert_pos;
    int *face_indice;

}st_mesh_data;

/**
 * @brief structure de 3 flotant
 */
typedef struct st_vec3
{
    float x;
    float y;
    float z;
}st_vec3;

/**
 * @brief permet de regroupper dans la même structure, divers paramètre d'un élément du monde
 * @param position la position de l'élément dans le monde
 * @param rotation la rotation de celui-ci
 * @param transformation si on modifie ça taille ou ce genre de choses
 */
typedef struct st_transform
{
    st_vec3 position;
    st_vec3 rotation;
    st_vec3 transformation;
}st_transform;

/**
 * @brief permet de regroupper au même endroit les information propore à l'apparence d'un éléments
 * @param shader est donc le shader lié à cet élément
 * @param texture la texture de celui-ci
 */
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

/**
 * @brief permet d'apporter des modification à des mesh instancier de manière individuel
 * @param model matrice model
 */
typedef struct st_instance_data
{
    mat4 model[16];
}st_instance_data;

/**
 * @brief structure d'élément instencier
 * @param cpu_data les données du model pour chaque instances
 * @param count le nombre de donnée actives
 * @param capacity le nombre max de données
 * @param vbo buffer de ces données côté GPU
 */
typedef struct st_instanced
{
    st_instance_data *cpu_data;
    int count;
    int capacity;
    unsigned int vbo;

}st_instanced;

/**
 * @brief groupe d'objets pour un rendu conventionnel
 * @param objects liste des objects
 * @param nb_objects nombre d'ojbjet dans la liste
 */
typedef struct st_mesh_group
{
    st_render_object *objects;
    int nb_objects;

}st_mesh_group;

/**
 * @brief groupe d'objets à instancier
 * @param shared_render_object le mesh à instancier
 * @param st_instanced données de l'instanciation
 */
typedef struct st_instanced_mesh_group
{
    st_render_object *shared_render_object;
    st_instanced st_instanced;

}st_instanced_mesh_group;


/**
 * @brief structure principal d'un group
 * @param ID identifaint du groupe
 * @param type type du groupe, cela affecte ça méthode de rendu
 * @param data redirige vers le strucutre qui contiennent les éléments du groupe en fonction de son type
 * @param init_group permet d'initialiser les informations de bases d'un groupe
 * @param add_element permet d'ajouter un élément au groupe
 * @param remove_element permet de supprimer un élément de ce groupe
 * @param get_element permet de récupéré un élément
 * @param remove_all_element supprime tout ces élément
 * @param generic_func_delete_group_object supprime le groupes
 */
typedef struct st_render_group st_render_group;

typedef struct vt_group_virtual_table
{
    int (* add_element)(void *void_group, st_render_object object);
    int (* remove_element)(void *void_group, int id);
    st_render_object* (* get_element)(void *void_group, int id);
    int (* remove_all_elements)(st_mesh_group *group);
    int (* delete_group_object)(st_render_group *group); 
}vt_group_virtual_table;


struct st_render_group
{
    int ID;
    e_render_group_type type;
    void *data;

    vt_group_virtual_table *tables;
};


#endif