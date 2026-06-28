#ifndef CONTROLLER_GAME_CONTEXT
#define CONTROLLER_GAME_CONTEXT

#include <stdio.h>

#include "../Model/model_game_context.h"
#include "../View/view_game_context.h"

#include "../../Shared_tools/Load_tools/load_shader.h"
#include "../../Shared_tools/Load_tools/load_obj_format.h"

#include "../../../types.h"

#include "../../../state.h"

#include "../../Controller/callback_controller.h"

void controller_update_render_game(st_render_data *render);
void init_game(st_state *state);
void controller_update_logic_game(st_state *state);


#endif
