#ifndef CONTEXT_STACK
#define CONTEXT_STACK

#include <stdio.h>
#include <stdlib.h>

#include "../../types.h"
#include "../Config/constantes.h"

#include "../Platform/glfw_input.h"

int link_context(st_context_tool *tools);
void put_context(st_stack *my_stack, st_context *my_state);
int remove_context(st_stack *my_stack);
int new_context(st_context *new_state, st_context_tool tools, st_stack *stack);

#endif