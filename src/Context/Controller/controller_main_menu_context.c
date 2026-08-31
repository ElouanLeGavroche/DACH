#include "../../../include/src_include/Context/Controller/controller_main_menu_context.h"


typedef enum
{
    MAIN_GROUP
}e_group_name;

typedef enum
{
    HOUSE,
    SQUARE,
    BACKGROUND_PLANE
}e_elt_name;

int init_menu(st_context *state)
{
    printf("début de l'initiation\n");
    int res;

    init_camera(&state->render.camera, 0.0f, 1000.0f, -1000.0f, 2.0f, 0.0f);
    init_camera_vector(&state->render.camera, (vec3){0.0f, 0.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){0.0f, 1.0f, 0.0f});
    init_camera_view(&state->render.camera);

    init_render_main_menu(&state->render);
    
    // CHARGER LES SHADERS --------------------------------------------------------------------------------------------
    st_shader *main_shader = new_shader("src/Shaders/shader_menu.vert", "src/Shaders/main_shader.frag");

    // Initialiser les éléments 3D --------------------------------------------------------------------------------------------
    st_mesh *house = new_object(BASIC_HOUSE_PATH);
    st_mesh *tile = new_object(BASIC_TILE_PATH);

    st_mesh *background = new_plane(-4.5f, -2.0f, 9.0f, 4.0f);
    st_transform background_plane_trans = configure_transform((st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});

    // Charger les textures
    st_texture *grass_texture = new_texture("ressources/images/grass_test.jpg");
    st_texture *background_plane_text = new_texture("ressources/images/main_menu_bg.jpg");

    // Creation du groupe
    res = add_group(&state->render, RENDER_GROUP_MESH, MAIN_GROUP);
    if(res != RES_DONE)
    {
        fprintf(stderr, "Erreur lors de la création du group.\n");
        return RES_ERROR;
    }
    
    st_render_group *group = get_group(state->render.groups, 0, state->render.nb_groups);

    // Définir les transformation
    st_transform house_transform = configure_transform((st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});
    st_transform floor = configure_transform((st_vec3){0.5, 0.5, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});

    // Définir les objets
    create_an_object(HOUSE, house, grass_texture, main_shader, house_transform, group);
    create_an_object(SQUARE, tile, grass_texture, main_shader, floor, group);
    create_an_object(BACKGROUND_PLANE, background, background_plane_text, main_shader, background_plane_trans, group);
    
    printf("Context menu initier\n");
    return RES_DONE;
}


void controller_update_logic_main_menu(st_context *state, int width, int height)
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