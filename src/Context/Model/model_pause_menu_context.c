#include "../../../include/src_include/Context/Model/model_pause_menu_context.h"

void update_logic_pause_menu(st_context *state)
{

    // Géré les inputs
    if(state->inputs.release[KEY_DOWN] == true)
    {
        state->request.target = C_BACK;
        state->request.action = CONTEXT_ACTION_POP;

        state->inputs.release[KEY_DOWN] = false;
    }
    if(state->inputs.release[KEY_ESCAPE] == true)
    {
        state->request.action = CONTEXT_ACTION_POP;
        state->request.target = C_GAME;
        
        state->inputs.release[KEY_ESCAPE] = false; 
    }

}
