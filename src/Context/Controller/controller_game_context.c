#include "../../../include/src_include/Context/Controller/controller_game_context.h"


typedef enum
{
    WORLD
}e_group_name;

typedef enum
{
    TILE
}e_elt_name;

struct st_state game_state =
{
    C_GAME,
    init_game,
    controller_update_logic_game,
    controller_update_render_game,
    
};

int init_game(st_state *state)
{
    printf("début de l'initiation\n");
    
    // CHARGER LES SHADERS --------------------------------------------------------------------------------------------
    st_shader shader = new_shader("src/Shaders/main_shader.vert", "src/Shaders/main_shader.frag");

    // Initialiser les éléments 3D --------------------------------------------------------------------------------------------
    st_mesh tile = new_object(BASIC_TILE_PATH);

    st_texture grass_texture = new_texture("ressources/images/grass_test.jpg");
    
    // Creation du groupe du monde
    add_group(&state->render, RENDER_GROUP_INSTANCED_MESH);
    st_render_group *group = get_group(state->render.groups, WORLD, state->render.nb_groups);
    
    
    // Définir les objets
    int i, y;
    int size_map = 52;
    for(i = size_map; i > 0; i --)
    {
        for(y = size_map; y > 0; y --)
        {
            st_transform floor = configure_transform((st_vec3){0.5, 0.5, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});
            create_an_object(TILE, tile, grass_texture, shader, floor, group);
    
        }
    }


    mat4 world_tile;
    init_world(&state->render, world_tile, 52*52);

    init_render_game(&state->render);

    // Initialiser le model --------------------------------------------------------------------------------------------
    init_data_game(state);

    // On passe la caméra dans la fenêtre pour les callbacks
    GLFWwindow *window = glfwGetCurrentContext();

    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->camera = &state->render.camera;

    glfwSetScrollCallback(window, scroll_callback);
    

    printf("Context jeu initier\n");
    return DONE;
}


void controller_update_logic_game(st_state *state)
{
    update_logic_game(state);
}

void controller_update_render_game(st_render_data *render)
{
    update_render_game(render);
}