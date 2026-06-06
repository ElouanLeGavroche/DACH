#include "../../include/src_include/Model/model_main_menu.h"

void init_menu()
{

}

void input_context_menu(st_engine *engine_state)
{
    // Système temporaire pour traiter les entrées
    if(engine_state->input.escape == true)
    {  
        engine_state->running = false;
    }
}

void update_logic_main_menu(st_engine *engine_state)
{
    if(engine_state->input.one_of_them){
        input_context_menu(engine_state);
    }
}