#ifndef VIEW_MAIN_MENU
#define VIEW_MAIN_MENU

#include <stdio.h>
#include <string.h>

#include "../../../../extern_lib/glad/glad.h"

#include <GLFW/glfw3.h>

#include "../../../types.h"
#include "../../Config/constantes.h"

#include "../../../../include/src_include/Shared_tools/Transform_openGL_values/colors.h"

#include "../../Shared_tools/Load_tools/load_shader.h"
#include "../../Shared_tools/Load_tools/load_obj_format.h"

#include "../../Shared_tools/List/Unsigned_list/unsigned_list.h"


/*
Ce n'est sans doute pas la meilleur solution, mais cela fera l'affaire pour le début
*/

// Les chemins des éléments du menu
#define BASIC_TILE_PATH "ressources/tiles/basic_tile.obj"

void init_render(st_engine *engine_state);
void update_render_main_menu(st_engine *engine_state);
void change_render_mode(st_engine *engine_state);

#endif