#include "../../include/src_include/Core/application.h"

int init_application(){
    int res;

    // Stock des informations pour le moteur
    st_engine engine_state;
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

    init_opengl();

    // On charge le premier context
    res = engine_state.context_tool.create_context(&main_menu_state);
    if(res != RES_DONE)
    {
        fprintf(stderr, "Echec de la création du contexte.\n");
        return RES_ERROR;
    }

    res = engine_state.context_tool.push_context(&main_menu_state, &engine_state.stack_context);
    if(res != RES_DONE)
    {
        fprintf(stderr, "Echec lors du poussage du contexte vers la stack.\n");
        return RES_ERROR;
    }

    link_input(engine_state.stack_context.current_context);
    link_mouse(engine_state.stack_context.current_context);

    if(res != RES_ERROR)
    {    
        /* -4- entrer dans les mains loops */
        mainloop(&engine_state);
    }
    else
    {
        fprintf(stderr, "Erreur lors de l'initialisation du contexte.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
    
}

/**
 * @brief Simplement la mainloop qui tourne sur le thread principale et qui orchestre le rendu
 * @param engin_state le moteur
 */
void mainloop(st_engine *engine_state){

    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;

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
        
        // Contenu //
        engine_state->stack_context.current_context->update_logic_context(engine_state->stack_context.current_context);

        //Actual context
        engine_state->stack_context.current_context->update_render_context(&engine_state->stack_context.current_context->render);
        
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