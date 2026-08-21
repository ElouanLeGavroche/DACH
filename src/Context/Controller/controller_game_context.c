#include "../../../include/src_include/Context/Controller/controller_game_context.h"

typedef enum
{
    TILE
}e_elt_name;

int init_game(st_context *state)
{
    printf("début de l'initiation\n");

    // Paramètre de la caméra 
    init_camera(&state->render.camera, 30.0f, 1000.0f, -1000.0f, 25.0f, 45.0f);
    init_camera_vector(&state->render.camera, (vec3){2.0f, 2.0f, 2.0f}, (vec3){0.450f, 0.250f, 0.450f}, (vec3){0.0f, 1.0f, 0.0f});
    init_camera_view(&state->render.camera);
    
    // Initialiser le rendu --------------------------------------------------------------------------------------------
    state->render.nb_groups = 0;
    state->render.nb_total_groups = 0;

    // CREATION DU MONDE    --------------------------------------------------------------------------------------------
    st_country_map_for_render *map = load_map("ressources/maps/fisel.json");

    /* Charger la carte */
    st_game_model *model = state->model;
    model->country = better_load_map("ressources/maps/fisel_v2.json");

    /* Parser la carte avant de l'envoyer au gpu */
    st_parsed_country *better_map = parse_country_data_for_gpu(model->country);
    
    /* On génère les données nécéssaire pour le GPU */
    create_render_world(state, map);

    // On passe la caméra dans la fenêtre pour les callbacks
    GLFWwindow *window = glfwGetCurrentContext();

    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->camera = &state->render.camera;
    
    printf("Context jeu initier\n");

    return RES_DONE;
}

void controller_update_logic_game(st_context *state)
{
    update_logic_game(state);
}

void controller_update_render_game(st_render_data *render, double time)
{
    update_render_game(render, time);
}


int better_create_render_world(st_context_request *state, st_parsed_country *map)
{
    if(!map)
    {
        fprintf(stderr, "La carte est null.\n");
        return RES_NULL_POINTER;
    }

    int i;
    for(i = 0; i < map->nb_group; i ++)
    {
        
    }
}

int create_render_world(st_context *state, st_country_map_for_render *map)
{
    // Chargement des éléments propre à la map
    int i;
    
    if(map == NULL)
    {
        fprintf(stderr, "Erreur lors du chargement de la map.\n");
        return RES_ERROR;
    }
    for(i = 0; i < map->nb_groups; i ++)
    {

        // CHARGER LES SHADERS ---------------------------------------------------------------------------------------------
        st_shader *shader = new_shader(map->groups[i].vert_shader, map->groups[i].frag_shader);
        if(!shader)
        {
            fprintf(stderr, "Erreur lors de la création d'un shader.\n");
            return RES_ERROR;
        }

        // CHARGER LES ELTS 3D ---------------------------------------------------------------------------------------------
        st_mesh *tile = new_object(map->groups[i].mesh);
        if(!tile)
        {
            fprintf(stderr, "Erreur lors de la création d'une tile.\n");
            return RES_ERROR;
        }

        // CHARGER LES TEXTURES --------------------------------------------------------------------------------------------
        st_texture *grass_texture = new_texture(map->groups[i].texture);
        if(!grass_texture)
        {
            fprintf(stderr, "Erreur lors de la création d'une texture.\n");
            return RES_ERROR;
        }

        // Creation du groupe du monde
        add_group(&state->render, RENDER_GROUP_INSTANCED_MESH);
        st_render_group *world_group = get_group(state->render.groups, map->groups[i].id, state->render.nb_groups);
        
        // On crée l'objet qui sera instancier
        st_transform floor = configure_transform((st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});
        create_an_object(TILE, tile, grass_texture, shader, floor, world_group);
        
        // Paramètre principaux du monde
        int world_size = map->groups[i].nb_blocks;
        mat4 *world_tile = init_map(map->groups[i].nb_blocks, map->groups[i].tiles);

        // Crée une variable tampon pour l'instanciation
        st_instanced *instenced_data = malloc(sizeof(st_instanced));
        create_an_instance(world_size, world_tile, instenced_data);

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


    // On free map
    free(map->groups->tiles);
    free(map->groups);
    free(map);
    map = NULL;

    return RES_DONE;
}

st_context* create_game_context()
{
    struct st_context *game_state = calloc(sizeof(st_context), sizeof(st_context));
    struct st_game_model *model = calloc(sizeof(st_game_model), sizeof(st_game_model));

    game_state->id = C_GAME;
    
    game_state->init_state = init_game;
    game_state->update_logic_context = controller_update_logic_game;
    game_state->update_render_context = controller_update_render_game;

    game_state->politicy.input_bellow = false;
    game_state->politicy.render_bellow = false;
    game_state->politicy.update_bellow = false;

    game_state->render.groups = NULL;
    game_state->render.nb_groups = 0;
    game_state->render.nb_total_groups = 0;

    game_state->request.action = CONTEXT_ACTION_NONE;
    game_state->request.target = C_NONE;

    game_state->model = model;

    return game_state;
}