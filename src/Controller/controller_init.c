#include "../../include/src_include/Controller/controller_init.h"

int controller_init(){
    // Stock des informations pour le moteur
    st_engine engine_state;

    // Variables pour les callbacks
    st_window_user_data *data = malloc(sizeof(st_window_user_data));
    GLFWwindow *window;

    // Integrer les paramètre de la fenêtre dans le callback
    data->window = &engine_state.window;

    /* Etape 1 : Création de la fenêtre et de son context */
    
    // -1- Charger les donnée propre à la fenêtre
    if(load_screen_data(&engine_state.window, &engine_state) == RES_ERROR){
        printf("Erreur lors de la récupération des données propre au contexte OpenGl.\n");

        return EXIT_FAILURE;
    }

    // -2- Initialiser la View
    if(init_View(&engine_state.window) == RES_ERROR){
        printf("Erreur lors de l'initialisation de la vue. \n");

        return EXIT_FAILURE;
    }

    // -3- Mise en place des Callbacks
    window = glfwGetCurrentContext();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetWindowUserPointer(window, data);
    
    /* -4- entrer dans les mains loops */
    controller_mainloop_management(&engine_state);

    // Free
    free(data);
    
    return EXIT_SUCCESS;
    
}