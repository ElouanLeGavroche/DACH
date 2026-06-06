#include "../../include/src_include/Controller/controller_mainloop.h"

void *logical_loop(void *data_engine)
{
    st_engine *engine_state = data_engine;
    // Partie Logique
    
    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;
    
    // Partie Model
    while(engine_state->running)
    {
        //Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        // Contenu //

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

    while(engine_state->running){
        //Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        // Géré les évènements par les entrée //
        process_input(input);

        // Système temporaire pour traiter les entrées
        if(input->escape == true)
        {
            engine_state->running = false;
        }

        view_clear();

        view_swap();

        // récupéré les entrées //
        glfwPollEvents();

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_frame(ts_start, ts_end);

    }
    //pthread_join(logical_thread, NULL);


    // Désalouer la mémoire avant la fermeture
    free(engine_state);
    free(input);

    view_close_window();
    while ( pthread_join(logical_thread, NULL));
    pthread_cancel(logical_thread);
    view_close_window();
}
