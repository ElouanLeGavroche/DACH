#ifndef CONTROLLER_GAME_CONTEXT
#define CONTROLLER_GAME_CONTEXT

#include <stdio.h>

#include "../Model/model_game_context.h"
#include "../View/view_game_context.h"

#include "../../Core/context_group.h"
#include "../../Core/context_stack.h"
#include "../../Core/context_camera.h"
#include "../../Core/context_content.h"

#include "../../Game/country.h"

#include "../../Platform/glfw_mouse.h"

#include "../../Shared_tools/Load_tools/load_map.h"

#include "../../../types.h"

#include "../../../state.h"

st_context* create_game_context();

void controller_update_render_game(st_render_data *render, double time);
int init_game(st_context *state);
int create_render_world(st_context *state, st_country_map_for_render *map);
void controller_update_logic_game(st_context *state);


#endif
