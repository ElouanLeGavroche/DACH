#include "../../../include/src_include/Context/Controller/controller_game_context.h"


typedef enum
{
    OTHER,
    INSTANCED_GROUP
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
    int i;
    init_render_game(&state->render);

    // Chargement des éléments propre à la map
    st_map *map = load_map("ressources/maps/fisel.json");

    for(i = 0; i < map->nb_groups; i ++)
    {

        // CHARGER LES SHADERS ---------------------------------------------------------------------------------------------
        st_shader *shader = new_shader(map->groups[i].vert_shader, map->groups[i].frag_shader);
    
        // CHARGER LES ELTS 3D ---------------------------------------------------------------------------------------------
        st_mesh *tile = new_object(map->groups[i].mesh);

        // CHARGER LES TEXTURES --------------------------------------------------------------------------------------------
        st_texture *grass_texture = new_texture(map->groups[i].texture);
        printf("%s\n", map->groups[i].texture);
        // Creation du groupe du monde
        add_group(&state->render, INSTANCED_GROUP);
        st_render_group *world_group = get_group(state->render.groups, map->groups[i].id, state->render.nb_groups);
        
        // On crée l'objet qui sera instancier
        st_transform floor = configure_transform((st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});
        create_an_object(TILE, tile, grass_texture, shader, floor, world_group);
        
        // Paramètre principaux du monde
        int world_size = map->groups[i].nb_blocks;
        mat4 *world_tile = init_map(map->groups[i].nb_blocks, map->groups[i].tiles);

        // Récuperer l'objet crée
        st_render_object *instenced_obj = world_group->tables->get_element(world_group, TILE);

        // Crée une variable tampon pour l'instanciation
        st_instanced *instenced_data = malloc(sizeof(st_instanced));
        create_an_instance(world_size, instenced_obj, world_tile, instenced_data);

        // Initialisation du monde
        create_an_instance_GPU(instenced_data, world_tile, world_size);

        // On attribue la valeur tampon à la structure
        st_instanced_mesh_group *instaced_group = (st_instanced_mesh_group *)world_group->data;
        instaced_group->st_instanced = *instenced_data;

        free(instenced_data);
        free(world_tile);

        instenced_data = NULL;
        world_tile = NULL;
    } 

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