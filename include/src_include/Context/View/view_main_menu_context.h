#ifndef VIEW_MAIN_MENU
#define VIEW_MAIN_MENU

#include <stdio.h>
#include <string.h>

#include "../../../../extern_lib/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../../types.h"

#include "../../../../include/src_include/Shared_tools/Transform_openGL_values/colors.h"

void init_render(st_engine *engine_state);
void update_render_main_menu(st_engine *engine_state);
void change_render_mode(st_engine *engine_state);

#endif