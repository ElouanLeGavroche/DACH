#include "../../include/src_include/Core/application.h"

int init_application(){
    int res;

    // Stock des informations pour le moteur
    st_engine engine_state = {0};
    st_window_user_data user_data = {
        .camera = NULL,
        .input = NULL,
        .mouse = NULL,
        .window = &engine_state.window  
    };

    // Initialisation des premières variables du moteur
    engine_state.running = true;
    engine_state.stack_context.level_of_depth = 0;
    engine_state.stack_context.current_context = NULL;

    if(init_window(&user_data, &engine_state.window) != RES_DONE)
    {
        fprintf(stderr, "Erreur lors du chargerment de la fenêtre.\n");
        return RES_ERROR;
    }
    
    if(link_context_tools_with_engine(&engine_state.context_tool) != RES_DONE)
    {
        fprintf(stderr, "Erreur lors du linkage avec les outils de context");
        return RES_ERROR;
    }

    // On crée le dictionnaire des context
    engine_state.all_contexts[C_GAME] = create_game_context;
    engine_state.all_contexts[C_MAIN_MENU] = create_main_menu_context;
    engine_state.all_contexts[C_PAUSE_MENU] = create_pause_menu_context;

    init_opengl();

    // On charge le premier context

    st_context *temp = engine_state.all_contexts[C_MAIN_MENU]();
    if(temp == NULL)
    {
        fprintf(stderr, "Erreur lors de la création du context.\n");
        return RES_ERROR;
    }
    res = engine_state.context_tool.create_context(temp);
    if(res != RES_DONE)
    {
        fprintf(stderr, "Echec lors du la création du contexte.\n");
        return RES_ERROR;
    }

    res = engine_state.context_tool.push_context(temp, &engine_state.stack_context);
    if(res != RES_DONE)
    {
        fprintf(stderr, "Echec lors du poussage du contexte vers la stack.\n");
        return RES_ERROR;
    }

    link_input(engine_state.stack_context.current_context);
    link_mouse(engine_state.stack_context.current_context);


    mainloop(&engine_state);

    return EXIT_SUCCESS;
    
}

/**
 * @brief Simplement la mainloop qui tourne sur le thread principale et qui orchestre le rendu
 * @param engin_state le moteur
 */
void mainloop(st_engine *engine_state){

    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double last = 0;

        ////////////////////////////////////////////
        //                                        //
        //                Boucle                  //
        //                                        //
        ////////////////////////////////////////////

    while(engine_state->running && window_should_close() != -1)
    {
        // Time au début de la boucle
        get_time(&ts_start);

        // récupéré les entrées //
        poll_events();

        view_clear();
        
        /**
         * Il y a ici une gestion du rendu/log/input du contexte actuel, mais aussi, et surtout, une gestion du rendu/log/input des contextes
         * parents, en fonction des politique du contexe actuel.
         */

        // Mettre à jour le temps du jeu //
        engine_state->dt_time =  get_glfw_time() - last;
        last = get_glfw_time();

        // Logique //
        update_logique(engine_state->stack_context, 0, engine_state->dt_time);
        // Rendu //
        update_render(engine_state->stack_context, 0, engine_state->dt_time);

        /* on va regarder s'il y a eu des requête fait pour les contextes */
        context_request(engine_state);

        view_swap();
        //Time fin de boucle
        get_time(&ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_frame(ts_start, ts_end);
    }
    view_close_window();
}

void update_logique(st_stack stack, int depth, double dt)
{
    if(stack.stack_context[depth]->politicy.update_bellow == true && depth + 1 < stack.level_of_depth)
    {
        update_logique(stack, depth + 1, dt);
    }
    stack.stack_context[depth]->update_logic_context(stack.stack_context[depth]);

}

void update_render(st_stack stack, int depth, double dt)
{
    if(stack.stack_context[depth]->politicy.render_bellow == true && depth + 1 < stack.level_of_depth)
    {
        update_render(stack, depth + 1, dt);
    }
    stack.stack_context[depth]->update_render_context(&stack.stack_context[depth]->render, dt);
}