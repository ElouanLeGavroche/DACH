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

void input_context_game(st_engine *engine_state)
{
    // Système temporaire pour traiter les entrées
    if(engine_state->input.escape == true)
    {  
        engine_state->running = false;
    }
    else if(engine_state->input.up_arrow == true)
    {
        engine_state->context_tool.put_context(&engine_state->stack_context, &game_state);
        engine_state->context_tool.level_of_depth ++;
        printf("%d\n", engine_state->context_tool.level_of_depth);
    }
    else if(engine_state->input.down_arrow == true)
    {
        if(engine_state->context_tool.remove_context(&engine_state->stack_context) == 0){
         
            engine_state->context_tool.level_of_depth --;
            printf("%d\n", engine_state->context_tool.level_of_depth);
        } 
    }

}

void controller_update_logic_game(st_engine *engine_state)
{
    update_logic_game(engine_state);
}

void controller_update_render_game(st_engine *engine_state)
{
    update_render_game(engine_state);
}