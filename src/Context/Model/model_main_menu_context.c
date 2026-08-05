#include "../../../include/src_include/Context/Model/model_main_menu_context.h"

void update_logic_main_menu(st_context *state)
{    
    // Géré les inputs
    if(state->inputs.release[KEY_UP] == true)
    {
        state->ev_next_context = C_GAME;   
        state->inputs.release[KEY_UP] = false;
    }
    if(state->inputs.release[KEY_ESCAPE] == true)
    {
        state->ev_must_close = true;   
        state->inputs.release[KEY_ESCAPE] = false;
    }
   
    /* On préviens l'autre thread que la lecture à bien été faite*/
    state->inputs.ok = true;
}
