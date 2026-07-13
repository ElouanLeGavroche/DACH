#include "../../types.h"

#include "../Shared_tools/Load_tools/load_shader.h"
#include "../Shared_tools/Load_tools/load_obj_format.h"
#include "../Shared_tools/Load_tools/load_image.h"

#include "../View/view_render_loop.h"


st_texture new_texture(char *path);
st_mesh new_object(char *path);
st_shader new_shader(char *path_vert, char *path_frag);
st_transform configure_transform(st_vec3 pos, st_vec3 rotation, st_vec3 transformation);