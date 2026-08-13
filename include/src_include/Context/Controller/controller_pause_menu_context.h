#ifndef CONTROLLER_PAUSE_MENU_CONTEXT
#define CONTROLLER_PAUSE_MENU_CONTEXT

#include "../../../types.h"

int init_pause_menu(st_context *state);
void controller_update_logic_pause_menu(st_context *state);
void controller_update_render_pause_menu(st_render_data *render, double time);
st_context* create_pause_menu_context();

#endif