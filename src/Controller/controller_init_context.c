#include "../../include/src_include/Controller/controller_init_context.h"

st_mesh new_object(char *path)
{
    st_mesh_data mesh_data = {0};
    st_mesh mesh;

    load_file(path, &mesh_data);

    mesh = init_a_3d_loaded_element(&mesh_data, 0);
    // On nettoye la structure côté CPU
    free(mesh_data.face_indice);
    free(mesh_data.vert_pos);
    
    return mesh;
}

st_texture new_texture(char *path)
{
    // CHARGER LES TEXTURES DES ELEMENTS --------------------------------------------------------------------------------------------
    st_image image = load_texture(path, 736, 552, 0);

    // Initialiser les Texutures des elements --------------------------------------------------------------------------------------------
    int texture_id = init_a_loaded_texture(&image);
    stbi_image_free(image.data);

    st_texture texture;
    texture.id = texture_id;
    texture.nb_occurences = 0;
    return texture;
}

st_shader new_shader(char *path_vert, char *path_frag)
{
    const char *vert = load_shader(path_vert);
    const char *frag = load_shader(path_frag);

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
    st_shader t_shader;
    t_shader.shader = shader;
    t_shader.nb_occurences = 0;

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