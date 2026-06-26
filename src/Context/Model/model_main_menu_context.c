#include "../../../include/src_include/Context/Model/model_main_menu_context.h"

void update_logic_main_menu(st_engine *engine_state)
{
    pthread_mutex_lock(&engine_state->stack_context.current_state->inputs.mutex); // Verrouillage
    
    // Géré les inputs
    if(engine_state->stack_context.current_state->inputs.release[KEY_UP] == true)
    {
        engine_state->stack_context.current_state->ev_next_context = C_GAME;   
    }
    if(engine_state->stack_context.current_state->inputs.release[KEY_ESCAPE] == true)
    {
        engine_state->stack_context.current_state->ev_must_close = true;   
    }

    pthread_mutex_unlock(&engine_state->stack_context.current_state->inputs.mutex); // Déverrouillage

    /* On préviens l'autre thread que la lecture à bien été faite*/
    engine_state->stack_context.current_state->inputs.ok = true;
}

void init_data_main_menu(st_state *state)
{
    // Initialiser les mutex
    pthread_mutex_init(&state->inputs.mutex, NULL);
}