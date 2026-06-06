#include "../../include/src_include/Controller/controller_init.h"

int controller_init(){
    // Stock les informations propre à la fenetre tel que la taille ou le frame rate dans une stucture défini dans types.h
    t_loaded_windows_data window_data;


    /* Etape 1 : Création de la fenêtre et de son context */
    
    // -1- Charger les donnée propre à la fenêtre
    if(load_screen_data(&window_data) == ERROR){
        printf("Erreur lors de la récupération des données propre au contexte OpenGl.\n");
        return EXIT_FAILURE;
    }

    // -2- Initialiser la View
    if(init_View(window_data) == ERROR){
        printf("Erreur lors de l'initialisation de la vue. \n");
        return EXIT_FAILURE;
    }

    /* Etape 2 : entrer dans les mains loops */
    controller_mainloop_management();

    return EXIT_SUCCESS;
    
}