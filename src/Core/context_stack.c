#include "../../include/src_include/Core/context_stack.h"

int link_context(void *put, void *remove)
{
    // Initialisation des outils de context
    put = put_context;
    if(!put)
    {
        fprintf(stderr, "Impossible de linker la stack context avec put.\n");
        return RES_FAILED_ASSIGNEMENT;
    }
    remove = remove_context;
    if(!remove)
    {
        fprintf(stderr, "Impossible de linker la stack context avec put.\n");
        return RES_FAILED_ASSIGNEMENT;
    }
    return RES_DONE;
}

// Essaie de structure file pour les etats
int remove_context(stack *my_stack)
{
    int return_status = EXIT_SUCCESS;

    if(my_stack->current_state->upper != NULL)
    {
        my_stack->current_state = my_stack->current_state->upper;
        // L'on incremente le niveau de profondeur
        my_stack->level_of_depth --;
    }
    else
    {
        printf("impossible de retirer cet éléments, il n'a pas de parents\n");
        return_status = EXIT_FAILURE;
    }
    printf("Le niveau de la stack : %d\n", my_stack->level_of_depth);
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

    // L'on incremente le niveau de profondeur
    my_stack->level_of_depth ++;
    printf("Niveau de la stack : %d\n", my_stack->level_of_depth);
    printf("context ajouter\n");
}