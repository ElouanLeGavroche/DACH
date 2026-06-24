#include "../../../include/src_include/Context/Controller/controller_main_menu_context.h"

struct st_state main_menu_state =
{
    init_menu,
    input_context_main_menu,
    controller_update_logic_main_menu,
    controller_update_render_main_menu
};

void init_menu(st_state *state)
{
    printf("début de l'initiation\n");

    // CHARGER LES SHADERS --------------------------------------------------------------------------------------------
    const char *vertex_shader_source = load_shader("src/Shaders/main_shader.vert");
    const char *fragment_shader_source = load_shader("src/Shaders/main_shader.frag");
    
    state->render.nb_shader = 1;

    // ""Gestion de l'erreur - lmao""
    if(!vertex_shader_source || !fragment_shader_source)
    {
        printf("Attention, certains shaders n'ont pas élé chargé"
        "Le comportement du programme peux-être compromis.\n");
    }
    
    // CHARGER LES ELEMENTS --------------------------------------------------------------------------------------------
    st_mesh first_square;
    load_file(BASIC_HOUSE_PATH, &first_square);

    st_mesh seconde_square;
    load_file(BASIC_TILE_PATH, &seconde_square);

    state->render.nb_mesh = 2;

    // Mallocs --------------------------------------------------------------------------------------------

    state->render.meshs = malloc(sizeof(st_mesh) * state->render.nb_mesh);
    state->render.shader_programs = malloc(sizeof(st_shader) * state->render.nb_shader);

    // Initialiser les shaders --------------------------------------------------------------------------------------------
    // Faire une fonction propre pour les charger individuellement ou par liste
    init_a_loaded_shader(&state->render, vertex_shader_source, fragment_shader_source);

    // Initialiser les éléments 3D --------------------------------------------------------------------------------------------
    init_a_3d_loaded_element(&state->render, &seconde_square, 0);
    init_a_3d_loaded_element(&state->render, &first_square, 1);
    
    free(seconde_square.face_pos);
    free(seconde_square.vert_pos);
    
    free(first_square.face_pos);
    free(first_square.vert_pos);


    // Libéré les shader qui sont compilé côté GPU à présent
    free((void *)vertex_shader_source);
    free((void *)fragment_shader_source);

    printf("Context menu initier\n");
}

int input_context_main_menu(st_input *inputs)
{
    // Système temporaire pour traiter les entrées
    GLFWwindow *window = glfwGetCurrentContext();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        return INP_CLOSE_GAME;
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        return INP_TO_GAME;
    }
    else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        return INP_CHANGE_RENDER_DEBUG;
    }
    return 0;
}

void controller_update_logic_main_menu(st_engine *engine_state)
{
    update_logic_main_menu(engine_state);
}

void controller_update_render_main_menu(st_render_data *render)
{
    update_render_main_menu(render);
}