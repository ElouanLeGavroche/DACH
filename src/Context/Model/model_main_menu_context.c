#include "../../../include/src_include/Context/Model/model_main_menu_context.h"

void update_logic_main_menu(st_context *state)
{    
    // Géré les inputs
    if(state->inputs.release[KEY_UP] == true)
    {
        state->request.action = CONTEXT_ACTION_PUSH;
        state->request.target = C_GAME;

        state->inputs.release[KEY_UP] = false;
    }
    if(state->inputs.release[KEY_ESCAPE] == true)
    {   

        state->request.action = CONTEXT_ACTION_QUIT;
        state->request.target = C_MAIN_MENU;
        
        state->inputs.release[KEY_ESCAPE] = false;
    }
   
    /* On préviens l'autre thread que la lecture à bien été faite*/
    state->inputs.ok = true;
}

/*
void *enter(st_stack stack, st_context state)
{
    return NULL;
}
    */