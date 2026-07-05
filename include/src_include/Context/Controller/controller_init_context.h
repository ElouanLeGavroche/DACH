#include "../../../types.h"

#include "../../Shared_tools/Load_tools/load_shader.h"
#include "../../Shared_tools/Load_tools/load_obj_format.h"
#include "../../Shared_tools/Load_tools/load_image.h"

#include "../../View/view_render_loop.h"


unsigned int new_texture(char *path);
st_mesh new_object(char *path);
unsigned int new_shader(char *path_vert, char *path_frag);