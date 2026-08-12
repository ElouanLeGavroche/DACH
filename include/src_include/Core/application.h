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
#include "context_request.h"

#include "../Platform/glfw_window.h"
#include "../Platform/glfw_input.h"

#include "../Renderer/opengl_renderer.h"


int init_application();
void mainloop(st_engine *engine_state);

void update_logique(st_stack stack, int depth);
void update_render(st_stack stack, int depth);

#endif