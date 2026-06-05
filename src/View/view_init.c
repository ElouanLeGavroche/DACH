#include "../../include/src_include/View/view_init.h"

int init_OpenGl(){
    /* Initialiser la librairie */

    if (!glfwInit())
        return ERROR;
    return DONE;
}


int init_Window(t_loaded_windows_data window_data){

    GLFWwindow *window = glfwCreateWindow(window_data.size_x, window_data.size_y, "Douar ar c'hornôg", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
}

int init_Keyboard(){
    glfwSetKeyCallback(glfwGetCurrentContext(), key_pressed);
}