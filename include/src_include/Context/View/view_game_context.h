#ifndef VIEW_GAME_CONTEXT
#define VIEW_GAME_CONTEXT

#include <stdio.h>

#include "../../../../extern_lib/glad/glad.h"
#include <GLFW/glfw3.h>

#include "../../../types.h"
#include "../../Config/constantes.h"



#include "../../View/view_render_loop.h"

// Les chemins des éléments du menu
#define BASIC_TILE_PATH "ressources/tiles/tile.obj"
#define BASIC_HOUSE_PATH "ressources/houses/house.obj"

void update_render_game(st_render_data *render);
void init_render_game(st_render_data *render);
void create_an_instance_GPU(st_instanced *instance, mat4 *model, int amount);

#endif