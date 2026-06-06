#include "../../include/src_include/Controller/controller_mainloop.h"

void *logical_loop(void *data_engine)
{
    // Partie Logique
    st_engine *engine_state = data_engine;
    
    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;
    
    // Partie Model
    while(engine_state->running)
    {
        //Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        // Contenu //
        update_logic_main_menu(engine_state);

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_tick(ts_start, ts_end);
    }

    printf("Thread logique mené à bien\n");
}



void controller_mainloop_management(){
    printf("Entrer dans la mainloop du jeu\n");
    ////////////////////////////////////////////
    //                                        //
    //  Initialisations des divers variables  //
    //                                        //
    ////////////////////////////////////////////

    // Thread qui tournera en parralèlle pour la logique. En outre
    // Il ne s'actualisera que 20 fois par seconde au le de 60
    // comme les graphismes
    pthread_t logical_thread;
    
    // Strucure qui contient toute les touches utile au jeu
    st_input *input = malloc(sizeof(st_input));
    input->escape = false;

    // Structure qui contient les divers variable "Globales" du moteur
    st_engine *engine_state = malloc(sizeof(st_engine));
    engine_state->running = true;
    engine_state->input = *input;

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

        view_clear();
        
        //Actual context
        update_visual_main_menu();

        view_swap();

        // récupéré les entrées //
        glfwPollEvents();

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_frame(ts_start, ts_end);

    }

    engine_state->running = false;
    while ( pthread_join(logical_thread, NULL));

    // Désalouer la mémoire avant la fermeture
    free(engine_state);
    free(input);

    view_close_window();
}
