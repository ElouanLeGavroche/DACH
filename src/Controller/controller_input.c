#include "../../include/src_include/Controller/controller_input.h"

void read_input(st_input *input)
{
    GLFWwindow *window = glfwGetCurrentContext();

    input->pressed[KEY_ESCAPE] = (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
    input->pressed[KEY_UP] = (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
    input->pressed[KEY_DOWN] = (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);
}