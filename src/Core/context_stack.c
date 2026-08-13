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
            for(i = 0; i < stack->level_of_depth; i ++) stack->stack_context[i] = stack->stack_context[i + 1];

            free(stack->current_context);
            stack->current_context = NULL;

            stack->current_context = stack->stack_context[0];

            if(stack->current_context == NULL || stack->stack_context[0] == NULL)
            {
                fprintf(stderr, "Quelque chose c'est mal passé.\n");
                return RES_NULL_POINTER;
            }
        }
        else
        {

            free(stack->current_context);
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
        for(i = stack->level_of_depth; i >= 0; i --) stack->stack_context[i + 1] = stack->stack_context[i];
        stack->stack_context[0] = new_context;
        stack->current_context = new_context;
        

        stack->level_of_depth ++;
    }
    return RES_DONE;
}

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