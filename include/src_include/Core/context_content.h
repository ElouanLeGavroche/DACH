#ifndef CONTEXT_CONTENT
#define CONTEXT_CONTENT

#include "../../types.h"

#include "../Shared_tools/Load_tools/load_shader.h"
#include "../Shared_tools/Load_tools/load_obj_format.h"
#include "../Shared_tools/Load_tools/load_image.h"

#include "../Renderer/opengl_renderer.h"


st_texture* new_texture(char *path);
st_mesh* new_object(char *path);
st_mesh* new_plane(float x, float y, float size_x, float size_y);
st_shader* new_shader(char *path_vert, char *path_frag);
st_transform configure_transform(st_vec3 pos, st_vec3 rotation, st_vec3 transformation);

#endif