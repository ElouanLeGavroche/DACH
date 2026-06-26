#include "../../../include/src_include/Context/Model/model_main_menu_context.h"

void update_logic_main_menu(st_engine *engine_state)
{
    // Géré les inputs
    if(engine_state->stack_context.current_state->inputs.release[KEY_ESCAPE] == true)
    {
        printf("Adieu\n");
    }
}

void init_data_main_menu(st_engine *engine)
{


}