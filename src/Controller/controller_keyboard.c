#include "../../include/src_include/Controller/controller_keyboard.h"

void key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods)
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