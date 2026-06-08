#ifndef CONTROLLER_MAIN_MENU_CONTEXT
#define CONTROLLER_MAIN_MENU_CONTEXT

#include <stdio.h>

#include "../Model/model_game_context.h"
#include "../View/view_game_context.h"

#include "../../../types.h"

#include "../../../state.h"

void controller_update_render_game(st_engine *engine_state);
void init_game(st_engine *engine_state);
void input_context_game(st_engine *engine_state);
void controller_update_logic_game(st_engine *engine_state);

#endif
