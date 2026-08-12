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
int old_exit_context(st_stack *stack)
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
        if(stack->level_of_depth > 1)
        {
            int i;
            printf("ok 1\n");
            stack->current_context = stack->stack_context[1];
            for(i = 0; i < stack->level_of_depth; i ++) stack->stack_context[i] = stack->stack_context[i + 1];
            printf("C'est fait.\n");
        }
        else
        {
            printf("ok 2\n");
            stack->current_context = NULL;
            stack->stack_context[0] = NULL;
        }

        stack->level_of_depth --;
    }

    return return_status;
}
int push_context(st_context *new_context, st_stack *stack)
{
    if(new_context == NULL)
    {
        fprintf(stderr, "Le nouveau context n'est pas prêt à être pousser.\n");
        return RES_ERROR;
    }

    if(stack->level_of_depth == MAX_CONTEXT)
    {
        fprintf(stderr, "Erreur, limite de context atteint. Si vous voulez en mettre plus, modifier la valeur de MAX_CONTEXT.\n");
        return RES_ERROR;
    }
    else
    {
        // Décalage des contextes
        int i;
        for(i = stack->level_of_depth; i > 0; i --) stack->stack_context[i + 1] = stack->stack_context[i];
        stack->stack_context[0] = new_context;
        stack->current_context = new_context;
        

        stack->level_of_depth ++;
    }
    printf("niveau de la stack : %d.\n", stack->level_of_depth);
    return RES_DONE;
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