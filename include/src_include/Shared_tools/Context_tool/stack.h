#ifndef MODEL_STACK
#define MODEL_STACK

#include <stdio.h>
#include <stdlib.h>

#include "../../../types.h"

void push_context(st_stack *my_stack, st_context *my_state);
int exit_context(st_stack *my_stack);
void afficher_stack(st_stack *my_stack);

#endif