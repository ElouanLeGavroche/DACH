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
    create_an_object(HOUSE, house, grass_texture, 0, 0, 0, group);
    create_an_object(SQUARE, tile, grass_texture, 0, 0, 0, group);

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