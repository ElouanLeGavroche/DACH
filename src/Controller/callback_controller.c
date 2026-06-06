#include "../../include/src_include/Controller/callback_controller.h"

void pressed_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    printf("touche entrée : %d\n", key);
    fflush(stdout);

}


void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}