#include "../../../include/src_include/Context/Model/model_game_context.h"


void update_logic_game(st_engine *engine_state)
{
    // Géré les inputs
    if(engine_state->stack_context.current_state->inputs.release[KEY_DOWN] == true)
    {
        engine_state->stack_context.current_state->next_context = C_BACK;   
    }
}

