#include "../../../include/src_include/Context/Controller/controller_game_context.h"

typedef enum
{
    TILE,
    PLANE
}e_elt_name;

int init_game(st_context *state)
{
    printf("début de l'initiation\n");
    int res;

    // Paramètre de la caméra 
    init_camera(&state->render.camera, 30.0f, -1000.0f, 1000.0f, 25.0f, 45.0f);
    init_camera_vector(&state->render.camera, (vec3){2.0f, 2.0f, 2.0f}, (vec3){0.450f, 0.250f, 0.450f}, (vec3){0.0f, 1.0f, 0.0f});
    init_camera_view(&state->render.camera);
    
    // Initialiser le rendu --------------------------------------------------------------------------------------------
    state->render.nb_groups = 0;
    state->render.nb_total_groups = 0;

    // CREATION DU MONDE    --------------------------------------------------------------------------------------------

    /* Charger la carte */
    st_game_model *model = state->model;
    model->country = better_load_map("ressources/maps/fisel_v2.json");
    /* Parser la carte avant de l'envoyer au gpu */
    st_parsed_country *better_map = parse_country_data_for_gpu(model->country);

    /* On génère les données nécéssaire pour le GPU */
    res = create_render_world(state, better_map);
    if(res != RES_DONE)
    {
        fprintf(stderr, "Erreur lors de la création de la map.\n");
        return RES_ERROR;
    }

    // On passe la caméra dans la fenêtre pour les callbacks
    GLFWwindow *window = glfwGetCurrentContext();

    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->camera = &state->render.camera;
    

    /* Essaie d'ajout d'un élément à la carte */

    // Step 1, crée la ville
    model->settlements = malloc(sizeof(st_settlement));
    model->settlements[0].id = 0;
    model->settlements[0].name = malloc(sizeof("Rostren"));
    model->settlements[0].parent_id = -1;

    // Step 2, Crée un object lié à cette ville
    model->objects = malloc(sizeof(st_object));
    model->objects[0].id = 1;
    model->objects[0].settlement_id = 0;
    model->objects[0].type = HOUSE;
    model->objects[0].subtype = LONG_ROCK_HOUSE;
    
    model->objects[0].x = -1.0f;
    model->objects[0].y = -1.0f;
    model->objects[0].w = 2.0f;
    model->objects[0].h = 2.0f;

    // On crée sont groupe
    res = add_group(&state->render, RENDER_GROUP_MESH, state->render.nb_groups + 1);
    if(res != RES_DONE)
    {
        fprintf(stderr, "Erreur lors de la création du groupe.\n");
        return RES_ERROR;
    }

    // On récuperer le groupebetter_load_map
    st_render_group *objects_group = get_group(state->render.groups, state->render.nb_groups, state->render.nb_groups);
    if(!objects_group)
    {
        fprintf(stderr, "Groupe non trouvé.\n");
        return RES_ERROR;
    }

    // CHARGER LES SHADERS ---------------------------------------------------------------------------------------------
    st_shader *shader = new_shader("src/Shaders/shader_menu.vert", "src/Shaders/main_shader.frag");
    if(!shader)
    {
        fprintf(stderr, "Erreur lors de la création d'un shader.\n");
        return RES_ERROR;
    }

    // On crée graphiquement l'objet
    st_mesh *bush = new_plane(model->objects[0].x, model->objects[0].y, model->objects[0].w, model->objects[0].h);
    if(!bush)
    {
        fprintf(stderr, "Erreur lors de la création d'une tile.\n");
        return RES_ERROR;
    }

    // CHARGER LES TEXTURES --------------------------------------------------------------------------------------------
    st_texture *grass_texture = new_texture("ressources/images/bushtest.png");
    if(!grass_texture)
    {
        fprintf(stderr, "Erreur lors de la création d'une texture.\n");
        return RES_ERROR;
    }

    // On crée l'objet qui sera instancier
    st_transform floor = configure_transform((st_vec3){4.0, 0.25, 2.0}, (st_vec3){90.0, 0.0, 0.0}, (st_vec3){1.0, 1.0, 1.0});
    create_an_object(PLANE, bush, grass_texture, shader, floor, objects_group);
    
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

/**
 * VERSION QUICK & DIRTY TEMPORAIRE !!
 */
int create_render_world(st_context *state, st_parsed_country *country)
{
    // Solution dirty pour que ce soit prêt se soir, il faudra refaire quelque chose de plus propre
    // Avec un .json qui sert de dicto
    if(!country)
    {
        fprintf(stderr, "La carte est null.\n");
        return RES_NULL_POINTER;
    }
    int i, res;

    char model[254];
    char vert[254];
    char frag[254];
    char texture[254];
    
    for(i = 0; i < country->nb_group; i ++)
    {
        bool empty = false;
        switch (country->groups[i].id)
        {
        case 1:
            strcpy(model, "ressources/tiles/tile.obj");
            strcpy(vert, "src/Shaders/main_shader.vert");
            strcpy(frag, "src/Shaders/main_shader.frag");
            strcpy(texture, "ressources/images/grass_test.jpg");

            break;
        case 2:
            strcpy(model, "ressources/tiles/tile.obj");
            strcpy(vert, "src/Shaders/main_shader.vert");
            strcpy(frag, "src/Shaders/main_shader.frag");
            strcpy(texture, "ressources/images/tank.jpg");

            break;
        default:
            empty = true;
            break;
        }
        printf("vide : %d, type : %d\n", empty, country->groups[i].id);
        if(!empty)
        {
            // CHARGER LES SHADERS ---------------------------------------------------------------------------------------------
            st_shader *shader = new_shader(vert, frag);
            if(!shader)
            {
                fprintf(stderr, "Erreur lors de la création d'un shader.\n");
                return RES_ERROR;
            }

            // CHARGER LES ELTS 3D ---------------------------------------------------------------------------------------------
            st_mesh *tile = new_object(model);
            if(!tile)
            {
                fprintf(stderr, "Erreur lors de la création d'une tile.\n");
                return RES_ERROR;
            }

            // CHARGER LES TEXTURES --------------------------------------------------------------------------------------------
            st_texture *grass_texture = new_texture(texture);
            if(!grass_texture)
            {
                fprintf(stderr, "Erreur lors de la création d'une texture.\n");
                return RES_ERROR;
            }

            // Creation du groupe du monde
            res = add_group(&state->render, RENDER_GROUP_INSTANCED_MESH, country->groups[i].id);
            if(res != RES_DONE)
            {
                fprintf(stderr, "Erreur lors de la création du groupe.\n");
                return RES_ERROR;
            }

            st_render_group *world_group = get_group(state->render.groups, country->groups[i].id, state->render.nb_groups);
            if(!world_group)
            {
                fprintf(stderr, "Groupe non trouvé.\n");
                return RES_ERROR;
            }

            // On crée l'objet qui sera instancier
            st_transform floor = configure_transform((st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});
            create_an_object(TILE, tile, grass_texture, shader, floor, world_group);
            
            // Paramètre principaux du monde
            int world_size = country->groups[i].nb_blocks;
            mat4 *world_tile = init_map(country->groups[i].nb_blocks, country->groups[i].tiles);

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
    }

    // On free map
    free(country->groups->tiles);
    free(country->groups);
    free(country);
    country = NULL;

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