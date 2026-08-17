#include "../../../include/src_include/Context/Controller/controller_pause_menu_context.h"

typedef enum
{
    MAIN_GROUP
}e_group_name;

typedef enum
{
    BACKGROUND_PLANE
}e_elt_name;

int init_pause_menu(st_context *state)
{
    int res;

    printf("Initialisation du menu pause.\n");

    init_camera(&state->render.camera, 0.0f, 1000.0f, -1000.0f, 2.0f, 0.0f);
    init_camera_vector(&state->render.camera, (vec3){0.0f, 0.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, (vec3){0.0f, 1.0f, 0.0f});
    init_camera_view(&state->render.camera);

    init_render_pause_menu(&state->render);

    st_shader *main_shader = new_shader("src/Shaders/shader_menu.vert", "src/Shaders/main_shader.frag");

    st_mesh *background_plane = new_plane(0.0f, 0.0f, 2.0f, 2.0f);
    st_transform background_plane_trans = configure_transform((st_vec3){0.5, 0.5, 0.0}, (st_vec3){0.0, 0.0, 0.0}, (st_vec3){0.0, 0.0, 0.0});
    
    st_texture *background_plane_text = new_texture("ressources/images/background.png");

    res = add_group(&state->render, RENDER_GROUP_MESH);
    if(res != RES_DONE)
    {
        fprintf(stderr, "Erreur lors de la création du groupe.\n");
        return RES_ERROR;
    }

    st_render_group *group = get_group(state->render.groups, 0, state->render.nb_total_groups);
    
    res = create_an_object(BACKGROUND_PLANE, background_plane, background_plane_text, main_shader, background_plane_trans, group);
    if(res != RES_DONE)
    {
        fprintf(stderr, "Erreur lors de la création de l'objet.\n");
        return RES_ERROR;
    }

    printf("Menu pause initier.\n");

    return RES_DONE;
}

void controller_update_logic_pause_menu(st_context *state)
{
    update_logic_pause_menu(state);
}

void controller_update_render_pause_menu(st_render_data *render, double time)
{
    update_render_pause_menu(render, time);
}

st_context* create_pause_menu_context()
{
    struct st_context *main_menu_state = calloc(sizeof(st_context), sizeof(st_context));

    main_menu_state->id = C_MAIN_MENU;
    
    main_menu_state->init_state = init_pause_menu;
    main_menu_state->update_logic_context = controller_update_logic_pause_menu;
    main_menu_state->update_render_context = controller_update_render_pause_menu;

    main_menu_state->politicy.input_bellow = false;
    main_menu_state->politicy.render_bellow = true;
    main_menu_state->politicy.update_bellow = false;

    return main_menu_state;
}