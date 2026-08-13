#include "../../../include/src_include/Context/Controller/controller_main_menu_context.h"


typedef enum
{
    TEST_GROUP,
    GOOFY_GROUP
}e_group_name;

typedef enum
{
    HOUSE,
    SQUARE
}e_elt_name;

int init_menu(st_context *state)
{
    printf("début de l'initiation\n");
    int res;

    printf("Initialisation de la caméra du contexte.\n");
    init_camera(&state->render.camera, 0.0f, 1000.0f, -1000.0f, 2.0f, 0.0f);
    init_camera_vector(&state->render.camera, (vec3){0.0f, 0.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){0.0f, 1.0f, 0.0f});
    init_camera_view(&state->render.camera);

    printf("Initialisation du rendu du contexte.\n");
    init_render_main_menu(&state->render);
    
    // CHARGER LES SHADERS --------------------------------------------------------------------------------------------
    printf("Initialisation des shaders du contexte.\n");
    st_shader *main_shader = new_shader("src/Shaders/shader_menu.vert", "src/Shaders/main_shader.frag");

    // Initialiser les éléments 3D --------------------------------------------------------------------------------------------
    printf("Initialisation des éléments 3D du contexte.\n");
    st_mesh *house = new_object(BASIC_HOUSE_PATH);
    st_mesh *tile = new_object(BASIC_TILE_PATH);

    // Charger les textures
    printf("Initialisation des textures contexte.\n");
    st_texture *grass_texture = new_texture("ressources/images/grass_test.jpg");
    
    // Creation du groupe
    printf("Initialisation des groupes du contexte.\n");
    res = add_group(&state->render, RENDER_GROUP_MESH);
    if(res != RES_DONE)
    {
        fprintf(stderr, "Erreur lors de la création du group.\n");
        return RES_ERROR;
    }
    
    st_render_group *group = get_group(state->render.groups, 0, state->render.nb_groups);

    // Définir les transformation
    printf("Initialisation des transformations du contexte.\n");
    st_transform house_transform = configure_transform((st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});
    st_transform floor = configure_transform((st_vec3){0.5, 0.5, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});

    // Définir les objets
    printf("Initialisation des objets du context.\n");
    create_an_object(HOUSE, house, grass_texture, main_shader, house_transform, group);
    create_an_object(SQUARE, tile, grass_texture, main_shader, floor, group);
    
    printf("Context menu initier\n");
    return RES_DONE;
}


void controller_update_logic_main_menu(st_context *state)
{
    update_logic_main_menu(state);
}

void controller_update_render_main_menu(st_render_data *render, double time)
{
    update_render_main_menu(render, time);
}

st_context* create_main_menu_context()
{
    st_context *main_menu_state = calloc(sizeof(st_context), sizeof(st_context));
    if(!main_menu_state)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return NULL;
    }
    main_menu_state->id = C_MAIN_MENU;
    
    main_menu_state->init_state = init_menu;
    main_menu_state->update_logic_context = controller_update_logic_main_menu;
    main_menu_state->update_render_context = controller_update_render_main_menu;

    main_menu_state->politicy.input_bellow = false;
    main_menu_state->politicy.render_bellow = false;
    main_menu_state->politicy.update_bellow = false;

    main_menu_state->render.groups = NULL;
    main_menu_state->render.nb_groups = 0;
    main_menu_state->render.nb_total_groups = 0;

    main_menu_state->request.action = CONTEXT_ACTION_NONE;
    main_menu_state->request.target = C_NONE;

    return main_menu_state;
}