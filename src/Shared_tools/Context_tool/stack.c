#include "../../../include/src_include/Shared_tools/Context_tool/stack.h"

// Essaie de structure file pour les etats
int remove_context(stack *my_stack)
{
    int return_status = EXIT_SUCCESS;

    if(my_stack->current_state->upper != NULL)
    {
        my_stack->current_state = my_stack->current_state->upper;
    }
    else
    {
        printf("impossible de retirer cet éléments, il n'a pas de parents\n");
        return_status = EXIT_FAILURE;
    }

    return return_status;
}

void put_context(stack *my_stack, st_state *my_state){
    /**
     * 2 cas : 1 stack vide, ajout simple
     *         2 stack non vide, remplacement nécéssaire  
     */    

    if(my_stack->current_state != NULL)
    {
        my_state->upper = my_stack->current_state;
    }
    my_stack->current_state = my_state;
    printf("context ajouter\n");
}

void afficher_stack(stack *my_stack){
    printf("Bonjour\n");
    //my_stack->current_state->st_state();
}