#ifndef CONTROLLER_MAIN_MENU_CONTEXT
#define CONTROLLER_MAIN_MENU_CONTEXT

#include <stdio.h>

#include "../Model/model_main_menu_context.h"
#include "../View/view_main_menu_context.h"

#include "../../../types.h"

#include "../../../state.h"

#include "controller_game_context.h"

void controller_update_render_main_menu(st_engine *engine_state);
void init_menu(st_engine *engine_state);
void input_context_main_menu(st_engine *engine_state);
void controller_update_logic_main_menu(st_engine *engine_state);

#endif
