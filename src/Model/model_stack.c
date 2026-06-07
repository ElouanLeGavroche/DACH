#include "../../include/src_include/Model/model_stack.h"

// Essaie de structure file pour les etats

int main(){

    printf("entrer en jeu\n");

    // Initialisation de la state globale
    stack my_stack = {0};

    // Création etat menu
    state menu = {0};
    menu.state = menu_render;
    menu.upper = NULL;
    
    // Création etat jeu
    state jeu = {0};
    jeu.state = game_render;
    jeu.upper = NULL;

    // Création etat jeu
    state opt = {0};
    opt.state = option_render;
    opt.upper = NULL;

    ajout_stack(&my_stack, &menu);
    afficher_stack(&my_stack);

    ajout_stack(&my_stack, &jeu);
    afficher_stack(&my_stack);

    back_stack(&my_stack);
    afficher_stack(&my_stack);

    ajout_stack(&my_stack, &opt);
    afficher_stack(&my_stack);

    ajout_stack(&my_stack, &jeu);
    afficher_stack(&my_stack);

    back_stack(&my_stack);
    afficher_stack(&my_stack);

    back_stack(&my_stack);
    afficher_stack(&my_stack);

    back_stack(&my_stack);
    afficher_stack(&my_stack);


    return EXIT_SUCCESS;

}

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

void ajout_stack(stack *my_stack, state *my_state){
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
    my_stack->current_state->state();
}

void menu_render(){
    printf("menu_render\n");
}

void game_render(){
    printf("game_render\n");
}

void option_render(){
    printf("option_render\n");
}

void pause_render(){
    printf("pause_render\n");
}