#include "../../include/src_include/Controller/callback_controller.h"

void pressed_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    printf("touche entrée : %d\n", key);
    fflush(stdout);
    /*
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwDestroyWindow(window);
        glfwTerminate();

        exit(EXIT_SUCCESS);
    }
        */
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}