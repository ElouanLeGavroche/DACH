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
    if(inputs->escape == true)
    {  
        return INP_CLOSE_GAME;
    }

    else if(inputs->down_arrow == true)
    {
        return INP_OLD_CONTEXT;
        
    }

}

void controller_update_logic_game(st_engine *engine_state)
{
    update_logic_game(engine_state);
}

void controller_update_render_game(st_engine *engine_state)
{
    update_render_game(&engine_state->stack_context.current_state->render);
}