#include "../../../include/src_include/Context/Model/model_main_menu_context.h"

void update_logic_main_menu(st_state *state)
{
    pthread_mutex_lock(&state->inputs.mutex); // Verrouillage
    
    // Géré les inputs
    if(state->inputs.release[KEY_UP] == true)
    {
        state->ev_next_context = C_GAME;   
    }
    if(state->inputs.release[KEY_ESCAPE] == true)
    {
        state->ev_must_close = true;   
    }

    pthread_mutex_unlock(&state->inputs.mutex); // Déverrouillage

    /* On préviens l'autre thread que la lecture à bien été faite*/
    state->inputs.ok = true;
}

void init_data_main_menu(st_state *state)
{
    // Initialiser les mutex
    pthread_mutex_init(&state->inputs.mutex, NULL);
}