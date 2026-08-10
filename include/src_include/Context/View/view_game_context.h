#ifndef VIEW_GAME_CONTEXT
#define VIEW_GAME_CONTEXT

#include <stdio.h>


#include "../../../types.h"
#include "../../Config/constantes.h"

#include "../../Platform/glfw_window.h"
#include "../../Renderer/opengl_renderer.h"
#include "../../Core/context_camera.h"
#include "../../Renderer/renderer.h"

#include "../../../../include/src_include/Shared_tools/Transform_openGL_values/colors.h"

// Les chemins des éléments du menu
#define BASIC_TILE_PATH "ressources/tiles/tile.obj"
#define BASIC_HOUSE_PATH "ressources/houses/house.obj"

void update_render_game(st_render_data *render);
void init_render_game(st_render_data *render);
void create_an_instance_GPU(st_instanced *instance, mat4 *model, int amount);
void init_game_camera(st_camera *camera);

#endif