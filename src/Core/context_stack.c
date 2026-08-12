#include "../../include/src_include/Core/context_stack.h"

int link_context_tools_with_engine(vt_context_tool *tools)
{
    // Initialisation des outils de context
    tools->push_context = push_context;
    if(!(tools->push_context))
    {
        fprintf(stderr, "Impossible de linker la stack context avec push.\n");
        return RES_FAILED_ASSIGNEMENT;
    }
    tools->exit_context = exit_context;
    if(!(tools->exit_context))
    {
        fprintf(stderr, "Impossible de linker la stack context avec exit.\n");
        return RES_FAILED_ASSIGNEMENT;
    }

    tools->create_context = create_context;
    if(!tools->create_context)
    {
        fprintf(stderr, "Impossible de linker la stack context avec create.\n");
        return RES_FAILED_ASSIGNEMENT;
    }
    return RES_DONE;
}

// Essaie de structure file pour les etats
int exit_context(st_stack *stack)
{
    int return_status = RES_DONE;
    if(stack->current_context == NULL)
    {
        fprintf(stderr, "Le context est null.\n");
        return_status = RES_NULL_POINTER;
    }
    else
    {
        if(stack->current_context->upper != NULL)
        {
            st_context *old_state = stack->current_context;
            stack->current_context = old_state->upper;

            //current_context = current_context->upper;
            // L'on incremente le niveau de profondeur
        }
        else
        {
            stack->current_context = NULL;
            // L'on incremente le niveau de profondeur
            
        }
        stack->level_of_depth --;
    }
    return return_status;
}

void push_context(st_context *new_context, st_stack *stack){
    /**
     * 2 cas : 1 stack vide, ajout simple
     *         2 stack non vide, remplacement nécéssaire  
     */    
    if(stack->current_context != NULL)
    {
        new_context->upper = stack->current_context;
    }
    stack->current_context = new_context;
    
    // On relie le clavier au nouveau context
    link_input(stack->current_context);

    // L'on incremente le niveau de profondeur
    stack->level_of_depth ++;
    printf("context ajouter\n");
}

int pause_context();
int resume_context();

int create_context(st_context *new_state)
{
    int res;
    
    // L'on initialise le nouveau context
    res = new_state->init_state(new_state);
    if(res == RES_ERROR)
    {
        printf("Erreur lors de l'initialisation du context.\n");
        return RES_ERROR;
    }

    return RES_DONE;

}