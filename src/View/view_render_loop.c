#include "../../include/src_include/View/view_render_loop.h"

void view_clear(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void view_swap(){
    // Récupéré le context openGL
    GLFWwindow *window = glfwGetCurrentContext();

    // Actualisation du swap
    glfwSwapBuffers(window);
}

void view_close_window(){
    glfwTerminate();
}

int window_should_close(){
    GLFWwindow *window = glfwGetCurrentContext();
    if (glfwWindowShouldClose(window))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}