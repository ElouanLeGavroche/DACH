#ifndef VIEW_MAIN_MENU
#define VIEW_MAIN_MENU

#include <stdio.h>
#include <string.h>

#include <math.h>

#include "../../../types.h"
#include "../../Config/constantes.h"

#include "../../Platform/glfw_window.h"
#include "../../../../include/src_include/Shared_tools/Transform_openGL_values/colors.h"

#include "../../Renderer/renderer.h"
// Les chemins des éléments du menu
#define BASIC_TILE_PATH "ressources/tiles/tile.obj"
#define BASIC_HOUSE_PATH "ressources/houses/house.obj"

void update_render_main_menu(st_render_data *render, double time);
void init_render_main_menu(st_render_data *render);

#endif