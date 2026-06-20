#include "../../../include/src_include/Context/Controller/controller_game_context.h"

struct st_state game_state =
{
    init_game,
    input_context_game,
    controller_update_logic_game,
    controller_update_render_game
};

void init_game(st_engine *engine_state)
{
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