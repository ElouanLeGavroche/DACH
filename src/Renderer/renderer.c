#include "../../include/src_include/Renderer/renderer.h"

void view_clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void view_swap(){
    // Récupéré le context openGL
    GLFWwindow *window = glfwGetCurrentContext();
    
    // Actualisation du swap
    glfwSwapBuffers(window);
}

void view_close_window(){
    GLFWwindow *window = glfwGetCurrentContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

int window_should_close(){
    if (glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}