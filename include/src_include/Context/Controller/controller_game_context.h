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

#include "../../Shared_tools/Math/ray_casting.h"

#include "../../../types.h"
#include "../../../state.h"

st_context* create_game_context();

void controller_update_render_game(st_render_data *render, double time);
int init_game(st_context *state);
int create_render_world(st_context *state, st_parsed_country *country);
void controller_update_logic_game(st_context *state, int width, int height);

st_country_tile* model_get_tile_at_world_pos(float iso_x, float iso_y, st_country *country, float tile_width, float tile_height, float tile_z_scale) ;

#endif
