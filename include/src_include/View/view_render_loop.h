#ifndef VIEW_RENDER_LOOP
#define VIEW_RENDER_LOOP

#include <stdbool.h>
#include <stdio.h>

#include "../../types.h"
#include "../Config/constantes.h"
#include "../../../extern_lib/glad/glad.h"

#include "../Shared_tools/List/Unsigned_list/unsigned_list.h"


#include <GLFW/glfw3.h>
#include <stdlib.h>

void view_close_window();
void view_swap();
void view_clear();
int window_should_close();

void init_a_loaded_shader(st_render_data *render, const char vertex_shader_source[], const char fragment_shader_source[]);
void init_a_3d_loaded_element(st_render_data *render, st_mesh *elt);


#endif