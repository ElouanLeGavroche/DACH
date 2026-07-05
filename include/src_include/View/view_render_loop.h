#ifndef VIEW_RENDER_LOOP
#define VIEW_RENDER_LOOP

#include <stdbool.h>
#include <stdio.h>

#include "../../types.h"
#include "../Config/constantes.h"
#include "../../../extern_lib/glad/glad.h"


#include <GLFW/glfw3.h>
#include <stdlib.h>

void view_close_window();
void view_swap();
void view_clear();
int window_should_close();

st_mesh init_a_3d_loaded_element(st_mesh *elt, int indice);
int init_a_loaded_shader(const char vertex_shader_source[], const char fragment_shader_source[]);
int init_a_loaded_texture(st_image *image);



#endif