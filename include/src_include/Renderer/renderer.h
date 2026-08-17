#ifndef RENDERER
#define RENDERER

#include "../Config/constantes.h"
#include "../../types.h"
#include "../../../extern_lib/glad/glad.h"
#include "../../../include/src_include/Shared_tools/Transform_openGL_values/colors.h"

void render_context(st_render_data *data, double time);

#endif