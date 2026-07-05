#include "../../../include/src_include/Context/Controller/controller_game_context.h"


typedef enum
{
    GROUP
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
    unsigned int shader = new_shader("src/Shaders/main_shader.vert", "src/Shaders/main_shader.frag");
    
    // Initialiser les éléments 3D --------------------------------------------------------------------------------------------
    st_mesh tile = new_object(BASIC_TILE_PATH);

    unsigned int grass_texture = new_texture("ressources/images/grass_test.jpg");

    // Creation du groupe
    add_group(&state->render, GROUP);
    st_group_world_obj *group = get_group(state->render.groups, GROUP, state->render.nb_groups);
    
    // Définir les objets
    int i, y;
    for(i = 25; i > 0; i --)
    {
        for(y = 0; y < i; y ++)
        {
            create_an_object(TILE + i, tile, grass_texture, (float)i*2.0f, (float)y*2.0f, 0, group);
        }
    }

    // Définir les shaders
    create_a_shader(shader, group);
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