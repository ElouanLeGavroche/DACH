#ifndef CONTEXT_STACK
#define CONTEXT_STACK

#include <stdio.h>
#include <stdlib.h>

#include "../../types.h"
#include "../Config/constantes.h"

#include "../Platform/glfw_input.h"

int link_context(vt_context_tool *tools);
void push_context(st_stack *my_stack, st_context *my_state);
int exit_context(st_stack *my_stack);
int create_context(st_context *new_state);
#endif