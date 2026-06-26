#include "../../../include/src_include/Context/Model/model_game_context.h"


void update_logic_game(st_engine *engine_state)
{
    // Géré les inputs
    if(engine_state->stack_context.current_state->inputs.release[KEY_DOWN] == true)
    {
        engine_state->stack_context.current_state->ev_next_context = C_BACK;   
    }
    if(engine_state->stack_context.current_state->inputs.release[KEY_ESCAPE] == true)
    {
        engine_state->stack_context.current_state->ev_must_close = true;   
    }
}

