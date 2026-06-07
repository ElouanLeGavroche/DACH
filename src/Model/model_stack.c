#include "../../include/src_include/Model/model_stack.h"

// Essaie de structure file pour les etats
void back_stack(stack *my_stack)
{
    if(my_stack->current_state->upper != NULL)
    {
        my_stack->current_state = my_stack->current_state->upper;
    }
    else
    {
        printf("impossible de retirer cet éléments, il n'a pas de parents\n");
    }
}

void ajout_stack(stack *my_stack, st_state *my_state){
    /**
     * 2 cas : 1 stack vide, ajout simple
     *         2 stack non vide, remplacement nécéssaire  
     */    
    if(my_stack->current_state != NULL)
    {
        my_state->upper = my_stack->current_state;
    }
    my_stack->current_state = my_state;
}

void afficher_stack(stack *my_stack){
    printf("Bonjour\n");
    //my_stack->current_state->st_state();
}