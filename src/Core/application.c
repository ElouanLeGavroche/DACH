#include "../../include/src_include/Core/application.h"

int init_application(){
    int res;

    // Stock des informations pour le moteur
    st_engine engine_state;
    
    // Initialisation des premières variables du moteur
    engine_state.running = true;
    engine_state.stack_context.level_of_depth = 0;
    engine_state.stack_context.current_state = NULL;

    if(init_window(&engine_state.window) == (RES_ERROR || RES_NULL_POINTER))
    {
        fprintf(stderr, "Erreur lors du chargerment de la fenêtre.\n");
        return RES_ERROR;
    }
    
    if(link_context(engine_state.context_tool.put_context, engine_state.context_tool.remove_context) == RES_FAILED_ASSIGNEMENT)
    {
        fprintf(stderr, "Erreur lors du linkage avec les outils de context");
        return RES_ERROR;
    }

    init_opengl();
    
    /* -4- entrer dans les mains loops */
    mainloop(&engine_state);
    
    return EXIT_SUCCESS;
    
}

/**
 * @brief Simplement la mainloop qui tourne sur le thread principale et qui orchestre le rendu
 * @param engin_state le moteur
 */
void mainloop(st_engine *engine_state){

    // Varibiable pour les erreurs
    int res;

    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;

    // On charge le premier context
    res = new_context(engine_state, &main_menu_state);
    if(res != RES_ERROR)
    {

            ////////////////////////////////////////////
            //                                        //
            //                Boucle                  //
            //                                        //
            ////////////////////////////////////////////

        while(engine_state->running && window_should_close() != -1){
            // Time au début de la boucle
            get_time(&ts_start);

            view_clear();
            
            // Contenu //
            engine_state->stack_context.current_state->update_logic_context(engine_state->stack_context.current_state);

            //Actual context
            engine_state->stack_context.current_state->update_render_context(&engine_state->stack_context.current_state->render);
            input_loop(engine_state);

            view_swap();

            //Time fin de boucle
            get_time(&ts_end);

            //Gestion de des conditions au calcul d'un nouveau tick
            wait_frame(ts_start, ts_end);

        }
        engine_state->running = false;
        unload_data(engine_state);
    }

    view_close_window();
}