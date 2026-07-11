#include "../../include/src_include/Model/model_mainloop.h"

double calculus_elapsed_time(struct timespec time_a, struct timespec time_b)
{
    // Calcule le temps qu'il reste (ou non) avant d'afficher l'image suivante
    return (time_b.tv_sec - time_a.tv_sec) + (time_b.tv_nsec - time_a.tv_nsec) / 1e9;

}


void wait_time(struct timespec time_a, struct timespec time_b, double elapsed, double time)
{
        // Temps de pause
        double sleep_sec =  time - elapsed;
        
        struct timespec time_sleep;
        
        time_sleep.tv_sec = (time_t) sleep_sec;
        time_sleep.tv_nsec = (long) ((sleep_sec - time_sleep.tv_sec) * 1e9);
        
        
        nanosleep(&time_sleep, NULL);
}

void wait_frame(struct timespec time_a, struct timespec time_b)
{
    /**
     * /!\ Attention : à la différence du calcul de tick, celui-ci peux rattrapper sont retard.
     */
    //Calcul de la pause en cas d'avance.
    double elapsed = calculus_elapsed_time(time_a, time_b);

    // Si on à du retard, on va alors calculer le temps que devra prendre la pause
    if(elapsed < TIME_PER_FRAME){
        wait_time(time_a, time_b, elapsed, TIME_PER_FRAME);
    }
    /*
    
    Ajouter le fait que la fonction peux choisir de sauter l'image suivante si elle voit que le rendu à du retard

    */
}

void wait_tick(struct timespec time_a, struct timespec time_b)
{
    /**
     * @brief Fait une pause de quelque nano secode en cas d'avance dans les calcul
     */

    //Calcul de la pause en cas d'avance.
    double elapsed = calculus_elapsed_time(time_a, time_b);

    // Si on à du retard, on va alors calculer le temps que devra prendre la pause
    if(elapsed < TIME_PER_TICK){
        wait_time(time_a, time_b, elapsed, TIME_PER_TICK);
    }

}