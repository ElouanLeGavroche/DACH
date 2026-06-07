#ifndef MODEL_STACK
#define MODEL_STACK

#include <stdio.h>
#include <stdlib.h>

#include "../../types.h"

#include "model_main_menu.h"

void put_context(stack *my_stack, st_state *my_state);
int remove_context(stack *my_stack);
void afficher_stack(stack *my_stack);

#endif