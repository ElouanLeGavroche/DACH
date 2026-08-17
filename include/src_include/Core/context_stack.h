#ifndef CONTEXT_STACK
#define CONTEXT_STACK

#include <stdio.h>
#include <stdlib.h>

#include "../../types.h"
#include "../Config/constantes.h"

#include "../Platform/glfw_input.h"

#include "../Renderer/opengl_renderer.h"

int link_context_tools_with_engine(vt_context_tool *tools);

int push_context(st_context *new_context, st_stack *stack);
int replace_context(st_context *new_context, st_stack *stack);
int exit_context(st_stack *stack);
int create_context(st_context *new_state);

#endif