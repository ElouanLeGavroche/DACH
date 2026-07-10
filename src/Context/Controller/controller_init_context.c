#include "../../../include/src_include/Context/Controller/controller_init_context.h"

st_mesh new_object(char *path)
{
    st_mesh_data mesh_data = {0};
    st_mesh mesh;

    load_file(path, &mesh_data);

    mesh = init_a_3d_loaded_element(&mesh_data, 0);

    return mesh;
}

unsigned int new_texture(char *path)
{
    // CHARGER LES TEXTURES DES ELEMENTS --------------------------------------------------------------------------------------------
    st_image texture = load_texture(path, 736, 552, 0);

    // Initialiser les Texutures des elements --------------------------------------------------------------------------------------------
    int texture_id = init_a_loaded_texture(&texture);
    stbi_image_free(texture.data);

    return texture_id;
}

unsigned int new_shader(char *path_vert, char *path_frag)
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

    return shader;
}
