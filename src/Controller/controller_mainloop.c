#include "../../include/src_include/Controller/controller_mainloop.h"

void *logical_loop(void *data_engine)
{
    // Partie Logique
    st_engine *engine_state = data_engine;
    
    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;
    // 
    // Partie Model
    while(engine_state->running)
    {
        //Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);
        
        // Contenu //
        engine_state->stack_context.current_state->update_logic_context(engine_state);
        
        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_tick(ts_start, ts_end);
    }

    printf("Thread logique mené à bien\n");
}



void controller_mainloop_management(st_engine *engine_state){
    ////////////////////////////////////////////
    //                                        //
    //  Initialisations des divers variables  //
    //                                        //
    ////////////////////////////////////////////

    // Thread qui tournera en parralèlle pour la logique. En outre
    // Il ne s'actualisera que 20 fois par seconde au le de 60
    // comme les graphismes
    pthread_t logical_thread;
    
    // Affichage du premier State (TEMP Main_menu)
    engine_state->context_tool.put_context(&engine_state->stack_context, &main_menu_state);

    //Initialiser le contenu de la State
    engine_state->stack_context.current_state->init_state(engine_state->stack_context.current_state);
    
    // Création du thread et passage de la structure engine
    pthread_create(&logical_thread, NULL, logical_loop, engine_state);

    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;

    // Ce tampon permet de savoir si le jeu est revenu à un etat entérieur
    // Et donc de recharger les éléments qui lui y étais associé
    int level_tampon = engine_state->stack_context.level_of_depth;
    int input_res = 0;
    ////////////////////////////////////////////
    //                                        //
    //                Boucle                  //
    //                                        //
    ////////////////////////////////////////////

    while(engine_state->running && !glfwWindowShouldClose(glfwGetCurrentContext())){
        // Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        // récupéré les entrées //
        glfwPollEvents();


        // Voir à quoi peuvent servir ces entrée dans ce context (si l'une d'entre elle est appuyé)

        input_res = engine_state->stack_context.current_state->input_context(&engine_state->input);
        if(input_res != 0)
        {
            // Ici on traite les actions à faire à l'échelle global, et non pas à l'échelle des context eux même
            switch (input_res)
            {
            case INP_CLOSE_GAME:
                engine_state->running = false;
                break;

            case INP_OLD_CONTEXT:
                engine_state->context_tool.remove_context(&engine_state->stack_context);
                break;

            case INP_TO_GAME:
                engine_state->next_state = &game_state;
                break;

            default:
                break;
            }
        }
            
        view_clear();
        
        //Actual context
        engine_state->stack_context.current_state->update_render_context(&engine_state->stack_context.current_state->render);

        view_swap();

        // Voir si un nouveau context est entré
        if(engine_state->next_state != 0)
        {
            // Chargement du nouveau context et déchargement de celui-ci
            new_context(engine_state);
            level_tampon = engine_state->stack_context.level_of_depth;
        }
        else if(level_tampon > engine_state->stack_context.level_of_depth)
        {
            // Déchargement du context actuel et rechargement du précédent
            level_tampon = engine_state->stack_context.level_of_depth;
            unload_data(engine_state);
            engine_state->stack_context.current_state->init_state(engine_state->stack_context.current_state);
        }

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_frame(ts_start, ts_end);

    }

    engine_state->running = false;
    pthread_join(logical_thread, NULL);

    unload_data(engine_state);

    view_close_window();
}

void new_context(st_engine *engine_state)
{
    unload_data(engine_state);

    //Initialiser le contenu de la State
    engine_state->next_state->init_state(engine_state->next_state);

    // L'on initialise le nouveau context
    engine_state->next_state->init_state(engine_state->stack_context.current_state);

    // L'on envoie le context suivant pour remplacer l'actuel
    engine_state->context_tool.put_context(&engine_state->stack_context, engine_state->next_state);
    
    // L'on supprime le context suivant qui est déjà placé
    engine_state->next_state = 0;

}

void unload_data(st_engine *engine_state)
{
    // Effacer les données de rendu
    destroy_render_data(&engine_state->stack_context.current_state->render);
    
    // Effacer les données de model
}


void destroy_render_data(st_render_data *render)
{

     int i;
    // On détruit tout les éléments de la liste
    for(i = 0; i < render->VAOs->size; i ++)
    {
        unsigned int vao = get_unsigned_int(render->VAOs, i);
        glDeleteVertexArrays(1, &vao);
    }
    
    for(i = 0; i < render->VBOs->size; i ++)
    {
        unsigned int vbo = get_unsigned_int(render->VBOs, i);
        glDeleteBuffers(1, &vbo);
    }
    
    for(i = 0; i < render->EBOs->size; i ++)
    {
        unsigned int ebo = get_unsigned_int(render->EBOs, i);
        glDeleteBuffers(1, &ebo);
    }

        for(i = 0; i < render->shader_programs->size; i ++)
    {
        unsigned int shader = get_unsigned_int(render->shader_programs, i);
        glDeleteProgram(shader);
    }
    
    destroy_unsigned_lst(render->VAOs);
    destroy_unsigned_lst(render->VBOs);
    destroy_unsigned_lst(render->EBOs);
    destroy_unsigned_lst(render->shader_programs);

    render->VAOs = NULL;
    render->VBOs = NULL;
    render->EBOs = NULL;
    render->shader_programs = NULL;

}