#ifndef CONTROLLER_GAME_CONTEXT
#define CONTROLLER_GAME_CONTEXT

#include <stdio.h>

#include "../Model/model_game_context.h"
#include "../View/view_game_context.h"

#include "../../Config/constantes.h"

#include "../../../types.h"

#include "../../../state.h"

void init_game(st_engine *engine_state);
void controller_update_logic_game(st_engine *engine_state);
void controller_update_render_game(st_engine *engine_state);

int input_context_game(st_input *inputs);

#endif
