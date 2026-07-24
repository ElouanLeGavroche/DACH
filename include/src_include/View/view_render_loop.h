#ifndef VIEW_RENDER_LOOP
#define VIEW_RENDER_LOOP

#include <stdbool.h>
#include <stdio.h>

#include "../../types.h"
#include "../Config/constantes.h"
#include "../../../extern_lib/glad/glad.h"

#include "../../../include/src_include/Shared_tools/Transform_openGL_values/colors.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

void view_close_window();
void view_swap();
void view_clear();
int window_should_close();

void view_render(st_render_data *render);
void view_instanced_render(st_render_group *void_group, st_camera *camera);
void view_normal_render(st_render_group *group);


st_mesh init_a_3d_loaded_element(st_mesh_data *elt, int indice);
int init_a_loaded_shader(const char vertex_shader_source[], const char fragment_shader_source[]);
int init_a_loaded_texture(st_image *image);

void render_mesh_group(st_mesh_group *group);


#endif