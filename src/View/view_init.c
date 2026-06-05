#include "../../include/src_include/View/view_init.h"

int init_View(t_loaded_windows_data window_data)
{
    
    if (!glfwInit())
        return ERROR;
    
    GLFWwindow *window = glfwCreateWindow(window_data.size_x, window_data.size_y, "Douar ar c'hornôg", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_pressed);

    return DONE;
}
