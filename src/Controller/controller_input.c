#include "../../include/src_include/Controller/controller_input.h"


void process_input(st_input *input)
{
    GLFWwindow *window = glfwGetCurrentContext();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        input->escape = true;
        input->one_of_them = true;
    }
    else{
        input->escape = false;
        input->one_of_them = false;
    }
}