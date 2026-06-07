#ifndef MODEL_STACK
#define MODEL_STACK

#include <stdio.h>
#include <stdlib.h>

#include "../../types.h"

void ajout_stack(stack *my_stack, state *my_state);
void back_stack(stack *my_stack);
void afficher_stack(stack *my_stack);

// Fonction de test
void menu_render();
void game_render();
void option_render();
void pause_render();


#endif