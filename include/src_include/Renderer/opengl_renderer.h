#ifndef OPENGL_RENDERER
#define OPENGL_RENDERER

#include "../Config/constantes.h"
#include "../../types.h"
#include "../../../extern_lib/glad/glad.h"


void init_opengl();

st_mesh init_a_3d_loaded_element(st_mesh_data *elt);
int init_a_loaded_shader(const char vertex_shader_source[], const char fragment_shader_source[]);
int init_a_loaded_texture(st_image *image);
#endif