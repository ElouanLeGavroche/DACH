#ifndef OPENGL_RENDERER
#define OPENGL_RENDERER

#include "../Config/constantes.h"
#include "../../types.h"
#include "../../../extern_lib/glad/glad.h"


void init_opengl();

st_mesh init_a_3d_loaded_element(st_mesh_data *elt);
st_mesh init_a_2d_plane(float x, float y, float size_x, float size_y);
int init_a_loaded_shader(const char vertex_shader_source[], const char fragment_shader_source[]);
int init_a_loaded_texture(st_image *image);


/* */
void gl_deletes();
void gl_delete_mesh(st_render_object *object);
void gl_delete_instanced_mesh(st_instanced *mesh);

void gl_delete_texture(unsigned int id);
void gl_delete_shader(unsigned int id);

void gl_finish();

void gl_update_view_port(int width, int height);

#endif