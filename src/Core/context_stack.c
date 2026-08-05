#include "../../include/src_include/Core/context_stack.h"

int link_context(vt_context_tool *tools)
{
    // Initialisation des outils de context
    tools->push_context = push_context;
    if(!(tools->push_context))
    {
        fprintf(stderr, "Impossible de linker la stack context avec put.\n");
        return RES_FAILED_ASSIGNEMENT;
    }
    tools->exit_context = exit_context;
    if(!(tools->exit_context))
    {
        fprintf(stderr, "Impossible de linker la stack context avec put.\n");
        return RES_FAILED_ASSIGNEMENT;
    }
    return RES_DONE;
}

// Essaie de structure file pour les etats
int exit_context(st_stack *my_stack)
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

void push_context(st_stack *my_stack, st_context *my_state){
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

int create_context(st_context *new_state, vt_context_tool tools, st_stack *stack)
{
    int res;
    
    // L'on initialise le nouveau context
    res = new_state->init_state(new_state);
    if(res == RES_ERROR)
    {
        printf("Erreur lors de l'initialisation du context.\n");
        return RES_ERROR;
    }

    tools.push_context(stack, new_state);
    stack->current_state->ev_next_context = C_NONE;
    // On relie le clavier au nouveau context
    link_input(new_state);
    return RES_DONE;

}