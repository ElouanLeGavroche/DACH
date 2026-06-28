#ifndef VIEW_MAIN_MENU
#define VIEW_MAIN_MENU

#include <stdio.h>
#include <string.h>

#include <math.h>

#include "../../../../extern_lib/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../../types.h"
#include "../../Config/constantes.h"

#include "../../View/view_render_loop.h"

#include "../../../../include/src_include/Shared_tools/Transform_openGL_values/colors.h"

// Les chemins des éléments du menu
#define BASIC_TILE_PATH "ressources/tiles/basic_tile.obj"
#define BASIC_HOUSE_PATH "ressources/houses/house.obj"

void update_render_main_menu(st_render_data *render);
void init_render_main_menu(st_render_data *render);

#endif