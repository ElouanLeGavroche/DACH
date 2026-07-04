#ifndef CONTROLLER_MAIN_MENU_CONTEXT
#define CONTROLLER_MAIN_MENU_CONTEXT

#include <stdio.h>

#include "../Model/model_main_menu_context.h"
#include "../View/view_main_menu_context.h"

#include "../../Model/model_group_context.h"

#include "controller_init_context.h"


#include "../../../types.h"
#include "../../../state.h"

void controller_update_render_main_menu(st_render_data *render);
int init_menu(st_state *state);
void controller_update_logic_main_menu(st_state *state);

#endif
