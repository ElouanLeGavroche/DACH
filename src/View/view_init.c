#include "../../include/src_include/View/view_init.h"

//#include VIEW_PATH "view_init.h"

int init_View(st_loaded_windows_data *window_data)
{
    
    if (!glfwInit())
        return ERROR;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(window_data->size_x, window_data->size_y, "Douar ar c'hornôg", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return ERROR;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(window);
        glfwTerminate();

        fprintf(stderr, "Failed to initialize GLAD\n");
        return ERROR;
    }

    /* Activer le test de profondeur */
    glEnable(GL_DEPTH_TEST);

    return DONE;
}