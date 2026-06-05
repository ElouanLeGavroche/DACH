#include "../../include/src_include/Controller/controller_mainloop.h"

void* logical_loop(void* arg){
    // Partie Logique

     //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;
    
    // Partie Model
    while(1)
    {
        //Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        // Contenu //

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_tick(ts_start, ts_end);

    }
    
}

void controller_mainloop_management(){
    printf("Entrer dans la mainloop du jeu\n");
    
    pthread_t logical_thread;
    pthread_create(&logical_thread, NULL, logical_loop, NULL);
    
    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;

    while(window_should_close()){
        //Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        view_clear();

        view_swap();

        // Gestion des entrées //
        glfwPollEvents();

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_frame(ts_start, ts_end);

    }
    pthread_cancel(logical_thread);
    view_close_window();

}
