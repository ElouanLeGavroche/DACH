#ifndef MODEL_STACK
#define MODEL_STACK

#include <stdio.h>
#include <stdlib.h>

#include "../../../types.h"

void put_context(st_stack *my_stack, st_state *my_state);
int remove_context(st_stack *my_stack);
void afficher_stack(st_stack *my_stack);

#endif