#include "../../include/src_include/Core/context_content.h"

st_mesh* new_object(char *path)
{
    st_mesh_data *mesh_data = malloc(sizeof(st_mesh_data));
    st_mesh *mesh = malloc(sizeof(st_mesh));
    if(!mesh)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return NULL;
    }

    load_file(path, mesh_data);

    *mesh = init_a_3d_loaded_element(mesh_data);
    // On nettoye la structure côté CPU
    free(mesh_data->face_indice);
    free(mesh_data->vert_pos);
    free(mesh_data);
    
    return mesh;
}

st_texture* new_texture(char *path)
{
    st_image image = load_texture(path, 736, 552, 0);
    st_texture *texture = malloc(sizeof(st_texture));
    if(!texture)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return NULL;
    }

    int texture_id = init_a_loaded_texture(&image);
    stbi_image_free(image.data);

    
    texture->id = texture_id;
    texture->nb_occurences = 0;
    return texture;
}

st_shader* new_shader(char *path_vert, char *path_frag)
{
    const char *vert = load_shader(path_vert);
    const char *frag = load_shader(path_frag);

    st_shader *t_shader = malloc(sizeof(st_shader));
    if(!t_shader)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return NULL;
    }

    // ""Gestion de l'erreur - lmao""
    if(!vert || !frag)
    {
        printf("Attention, certains shaders n'ont pas élé chargé"
        "Le comportement du programme peux-être compromis.\n");
    }
    // Initialiser les shaders --------------------------------------------------------------------------------------------
    unsigned int shader = init_a_loaded_shader(vert, frag);

    free((void *)vert);
    free((void *)frag);

    // Définir les shaders
    t_shader->shader = shader;
    t_shader->nb_occurences = 0;

    return t_shader;
}


st_transform configure_transform(st_vec3 pos, st_vec3 rotation, st_vec3 transformation)
{
    st_transform transform;
    transform.position = pos;
    transform.rotation = rotation;
    transform.transformation = transformation;

    return transform;
}