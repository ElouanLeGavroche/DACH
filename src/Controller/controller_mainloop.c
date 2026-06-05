#include "../../include/src_include/Controller/controller_mainloop.h"

void graphical_loop(){
    // Partie graphique

     //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;

    while(window_should_close()){
        //Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        view_clear();

        printf("Une image passé\n");

        view_swap();

        // Gestion des entrée
        glfwPollEvents();

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_frame(ts_start, ts_end);

    }
    view_close_window();
}

void controller_mainloop_management(){
    printf("Entrer dans la mainloop du jeu\n");
    

    __pid_t pid = fork();
    
    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;

    if(pid == 0)
    {
        // Partie graphique
        while(window_should_close()){
            //Time au début de la boucle
            clock_gettime(CLOCK_MONOTONIC, &ts_start);

            view_clear();

            printf("Une image passé\n");

            view_swap();

            // Gestion des entrée
            glfwPollEvents();

            //Time fin de boucle
            clock_gettime(CLOCK_MONOTONIC, &ts_end);

            //Gestion de des conditions au calcul d'un nouveau tick
            wait_frame(ts_start, ts_end);

        }
        view_close_window();
        closed = true;
    }
    else
    {
        // Partie Model
        while(!*closed)
        {
            //Time au début de la boucle
            clock_gettime(CLOCK_MONOTONIC, &ts_start);

            // Contenu
            printf("Un tick passé\n");

            //Time fin de boucle
            clock_gettime(CLOCK_MONOTONIC, &ts_end);

            //Gestion de des conditions au calcul d'un nouveau tick
            wait_tick(ts_start, ts_end);

        }

       
    }

}
