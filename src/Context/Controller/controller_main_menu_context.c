#include "../../../include/src_include/Context/Controller/controller_main_menu_context.h"


typedef enum
{
    TEST_GROUP
}e_group_name;

typedef enum
{
    HOUSE,
    SQUARE
}e_elt_name;

struct st_state main_menu_state =
{
    C_MAIN_MENU,
    init_menu,
    controller_update_logic_main_menu,
    controller_update_render_main_menu
};

st_mesh new_object(char *path)
{
    st_mesh mesh = {0};
    load_file(path, &mesh);

    mesh = init_a_3d_loaded_element(&mesh, 0);

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

int init_menu(st_state *state)
{
    printf("début de l'initiation\n");

    init_render_main_menu(&state->render);
    
    // CHARGER LES SHADERS --------------------------------------------------------------------------------------------
    unsigned int shader = new_shader("src/Shaders/main_shader.vert", "src/Shaders/main_shader.frag");

    // Initialiser les éléments 3D --------------------------------------------------------------------------------------------
    st_mesh house = new_object(BASIC_HOUSE_PATH);
    st_mesh tile = new_object(BASIC_TILE_PATH);

    unsigned int grass_texture = new_texture("ressources/images/grass_test.jpg");

    // Creation du groupe
    add_group(&state->render, TEST_GROUP);
    st_group_world_obj *group = get_group(state->render.groups, TEST_GROUP, state->render.nb_groups);


    // Définir les objets
    create_an_object(HOUSE, house, grass_texture, group);
    create_an_object(SQUARE, tile, grass_texture, group);

    // Définir les shaders
    create_a_shader(shader, group);

    // Initialiser le model --------------------------------------------------------------------------------------------
    init_data_main_menu(state);

    printf("Context menu initier\n");
    return DONE;
}


void controller_update_logic_main_menu(st_state *state)
{
    update_logic_main_menu(state);
}

void controller_update_render_main_menu(st_render_data *render)
{
    update_render_main_menu(render);
}