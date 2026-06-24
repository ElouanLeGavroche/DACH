#ifndef VIEW_GAME_CONTEXT
#define VIEW_GAME_CONTEXT

#include <stdio.h>

#include "../../../../extern_lib/glad/glad.h"
#include <GLFW/glfw3.h>

#include "../../../types.h"
#include "../../Config/constantes.h"

#include "../../View/view_render_loop.h"

#include "../../../../include/src_include/Shared_tools/Transform_openGL_values/colors.h"

// Les chemins des éléments du menu
#define BASIC_TILE_PATH "ressources/tiles/basic_tile.obj"
#define BASIC_HOUSE_PATH "ressources/houses/house.obj"

void update_render_game(st_render_data *render);

#endif