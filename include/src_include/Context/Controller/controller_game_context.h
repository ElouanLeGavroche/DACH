#ifndef CONTROLLER_GAME_CONTEXT
#define CONTROLLER_GAME_CONTEXT

#include <stdio.h>

#include "../Model/model_game_context.h"
#include "../View/view_game_context.h"

#include "../../Core/context_group.h"
#include "../../Core/context_stack.h"
#include "../../Core/context_camera.h"
#include "../../Core/context_content.h"

#include "../../Platform/glfw_mouse.h"

#include "../../Shared_tools/Load_tools/load_map.h"

#include "../../../types.h"

#include "../../../state.h"

void controller_update_render_game(st_render_data *render);
int init_game(st_state *state);
int controller_create_world(st_state *state);
void controller_update_logic_game(st_state *state);


#endif
