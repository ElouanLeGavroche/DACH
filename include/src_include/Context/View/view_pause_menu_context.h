#ifndef VIEW_PAUSE_MENU_CONTEXT
#define VIEW_PAUSE_MENU_CONTEXT

#include <stdio.h>
#include <string.h>

#include <math.h>

#include "../../../types.h"
#include "../../Config/constantes.h"

#include "../../Platform/glfw_window.h"
#include "../../../../include/src_include/Shared_tools/Transform_openGL_values/colors.h"

#include "../../Renderer/renderer.h"
// Les chemins des éléments du menu


void update_render_pause_menu(st_render_data *render, double time);
void init_render_pause_menu(st_render_data *render);


#endif