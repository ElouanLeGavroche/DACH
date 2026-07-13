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
    
    // CHARGER LES SHADERS ---------------------------------------------------------------------------------------------
    st_shader shader = new_shader("src/Shaders/main_shader.vert", "src/Shaders/main_shader.frag");

    // CHARGER LES ELTS 3D ---------------------------------------------------------------------------------------------
    st_mesh tile = new_object(BASIC_TILE_PATH);

    // CHARGER LES TEXTURES --------------------------------------------------------------------------------------------
    st_texture grass_texture = new_texture("ressources/images/grass_test.jpg");
    
    // Creation du groupe du monde
    add_group(&state->render, RENDER_GROUP_INSTANCED_MESH);
    st_render_group *world_group = get_group(state->render.groups, WORLD, state->render.nb_groups);
    
    // On crée l'objet qui sera instancier
    st_transform floor = configure_transform((st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});
    create_an_object(TILE, tile, grass_texture, shader, floor, world_group);
    
    // Paramètre principaux du monde
    int world_size = 52*52;
    mat4 *world_tile = init_map(world_size);
    

    // Récuperer l'objet crée
    st_render_object *instenced_obj = world_group->tables->get_element(world_group, TILE);

    // Crée une variable tampon pour l'instanciation
    st_instanced *instenced_data = malloc(sizeof(st_instanced));
    create_an_instance(world_size, instenced_obj, world_tile, instenced_data);

    // Initialisation du monde
    init_world(instenced_data, world_tile, world_size);
    
    // On attribue la valeur tampon à la structure
    st_instanced_mesh_group *instaced_group = (st_instanced_mesh_group *)world_group->data;
    instaced_group->st_instanced = *instenced_data;
    free(instenced_data);
    printf("ici : %d\n", instaced_group->st_instanced.count);

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