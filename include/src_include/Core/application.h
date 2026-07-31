#ifndef APPLICATION
#define APPLICATION

#include <stdlib.h>
#include <stdio.h>

#include "../Config/constantes.h"
#include "../../state.h"
#include "../../types.h"

#include "clock.h"
#include "context_stack.h"
#include "context_group.h"

#include "../Platform/glfw_window.h"
#include "../Platform/glfw_input.h"

#include "../Renderer/opengl_renderer.h"
#include "../Renderer/renderer.h"


int init_application();
void mainloop(st_engine *engine_state);
void unload_data(st_engine *engine_state);
void destroy_render_data(st_render_data *render);
void references_object_test(st_render_object *object);
void link_input(st_engine *engine_state);

#endif