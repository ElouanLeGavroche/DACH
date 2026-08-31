#ifndef CONTROLLER_PAUSE_MENU_CONTEXT
#define CONTROLLER_PAUSE_MENU_CONTEXT

#include "../../../types.h"
#include "../../../state.h"

#include "../View/view_pause_menu_context.h"
#include "../Model/model_pause_menu_context.h"

#include "../../Core/context_group.h"
#include "../../Core/context_stack.h"
#include "../../Core/context_camera.h"
#include "../../Core/context_content.h"

int init_pause_menu(st_context *state);
void controller_update_logic_pause_menu(st_context *state, int width, int height);
void controller_update_render_pause_menu(st_render_data *render, double time);
st_context* create_pause_menu_context();

#endif