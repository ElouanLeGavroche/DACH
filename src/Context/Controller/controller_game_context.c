#include "../../../include/src_include/Context/Controller/controller_game_context.h"

struct st_state game_state =
{
    init_game,
    input_context_game,
    controller_update_logic_game,
    controller_update_render_game
};

void init_game(st_state *state)
{
    printf("début de l'initiation\n");

    // CHARGER LES SHADERS --------------------------------------------------------------------------------------------
    const char *vertex_shader_source = load_shader("src/Shaders/main_shader.vert");
    const char *fragment_shader_source = load_shader("src/Shaders/main_shader.frag");
    
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
    
    // Initialiser le rendu --------------------------------------------------------------------------------------------
    //st_render_data *render = &engine_state->stack_context.current_state->render;
    init_unsigned_int_lst(&state->render.VAOs);
    init_unsigned_int_lst(&state->render.VBOs);
    init_unsigned_int_lst(&state->render.EBOs);
    init_unsigned_int_lst(&state->render.shader_programs);
    
    // Initialiser les shaders --------------------------------------------------------------------------------------------
    // Faire une fonction propre pour les charger individuellement ou par liste
    init_a_loaded_shader(&state->render, vertex_shader_source, fragment_shader_source);

    // Initialiser les éléments 3D --------------------------------------------------------------------------------------------
    init_a_3d_loaded_element(&state->render, &seconde_square);

    free(seconde_square.face_pos);
    free(seconde_square.vert_pos);

    init_a_3d_loaded_element(&state->render, &first_square);
    
    free(first_square.face_pos);
    free(first_square.vert_pos);

    // Libéré les shader qui sont compilé côté GPU à présent
    free((void *)vertex_shader_source);
    free((void *)fragment_shader_source);

    printf("Context jeu initier\n");
}

int input_context_game(st_input *inputs)
{
    // Système temporaire pour traiter les entrées
    GLFWwindow *window = glfwGetCurrentContext();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        return INP_CLOSE_GAME;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        return INP_OLD_CONTEXT;
    }
    else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        return INP_CHANGE_RENDER_DEBUG;
    }

    return 0;
}

void controller_update_logic_game(st_engine *engine_state)
{
    update_logic_game(engine_state);
}

void controller_update_render_game(st_render_data *render)
{
    update_render_game(render);
}