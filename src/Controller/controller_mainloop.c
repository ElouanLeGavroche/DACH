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
    engine_state->stack_context.current_state->init_state(engine_state);
    
    // Création du thread et passage de la structure engine
    pthread_create(&logical_thread, NULL, logical_loop, engine_state);

    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;

    ////////////////////////////////////////////
    //                                        //
    //                Boucle                  //
    //                                        //
    ////////////////////////////////////////////

    while(engine_state->running && !glfwWindowShouldClose(glfwGetCurrentContext())){
        // Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        // Mettre à jour le tableau des entrée //
        process_input(&engine_state->input);

        // Voir à quoi peuvent servir ces entrée dans ce context (si l'une d'entre elle est appuyé)
        if(engine_state->input.one_of_them)
        {
            engine_state->stack_context.current_state->input_context(engine_state);
        }
        // Voir si un nouveau context est entré
        if(engine_state->stack_context.next_state != 0)
        {
            new_context(engine_state);
        }

        view_clear();
        
        //Actual context
        engine_state->stack_context.current_state->update_render_context(engine_state);

        view_swap();

        // récupéré les entrées //
        glfwPollEvents();

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_frame(ts_start, ts_end);

    }

    engine_state->running = false;
    pthread_join(logical_thread, NULL);

    // Désalouer la mémoire avant la fermeture
    free(engine_state);

    view_close_window();
}

void new_context(st_engine *engine_state)
{

    // L'on initialise le nouveau context
    engine_state->stack_context.next_state->init_state(engine_state);

    // L'on envoie le context suivant pour remplacer l'actuel
    engine_state->context_tool.put_context(&engine_state->stack_context, engine_state->stack_context.next_state);
    
    // L'on supprime le context suivant qui est déjà placé
    engine_state->stack_context.next_state = 0;
    
    // L'on incremente le niveau de profondeur
    engine_state->stack_context.level_of_depth ++;
}

void old_context(st_engine *engine_state)
{
    if(engine_state->context_tool.remove_context(&engine_state->stack_context) == 0){
         
        engine_state->stack_context.level_of_depth --;
        printf("%d\n", engine_state->stack_context.level_of_depth);
    } 
}