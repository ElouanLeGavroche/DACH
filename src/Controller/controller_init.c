#include "../../include/src_include/Controller/controller_init.h"
#include "../../include/src_include/Controller/controller_mainloop.h"

int controller_init_graphic_lib(){
    return init_OpenGl();
}

int controller_get_screen_data(t_loaded_windows_data *window_data){
    return load_screen_data(window_data);
}

int controller_init_window(t_loaded_windows_data window_data){
    return init_Window(window_data);
}

int controller_init(){
    // Stock les informations propre à la fenetre tel que la taille ou le frame rate dans une stucture défini dans type.h
    t_loaded_windows_data window_data;
    /* Etape 1 : Initialiser la librairie Grapgique dans le View*/
    if(controller_init_graphic_lib() == ERROR){
        printf("Erreur lors de l'initialisation de la bibliothèque graphique.\n");
        return EXIT_FAILURE;
    }

    /* Etape 2 : Création de la fenêtre et de son context */
    
    // -1- Charger les donnée propre à la fenêtre
    if(controller_get_screen_data(&window_data) == ERROR){
        printf("Erreur lors de la récupération des données propre au contexte OpenGl.\n");
        return EXIT_FAILURE;
    }

    // -2- Crée le contexte OpenGL
    if(controller_init_window(window_data) == ERROR){
        printf("Erreur lors de la création de la fenêtre\n");
        return EXIT_FAILURE;
    }

    /* Etape 3 : Fork entre le rendu et le programe avec un système de verroux*/
    controller_mainloop_management();

    return EXIT_SUCCESS;
    
}