#ifndef controller_main_menu_context
#define controller_main_menu_context

#include <stdio.h>

#include "../Model/model_main_menu_context.h"
#include "../View/view_main_menu_context.h"

#include "../../../types.h"

#include "../../../state.h"

void controller_update_render_game(st_engine *engine_state);
void init_game(st_engine *engine_state);
void input_context_game(st_engine *engine_state);
void controller_update_logic_game(st_engine *engine_state);

#endif
