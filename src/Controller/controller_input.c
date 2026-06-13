#include "../../include/src_include/Controller/controller_input.h"


/**
 * @brief Système limité, temporaire. J'ai que 3 touche de mappé, et je vois déjà comment se sera la merdre à la fin.
 */
void process_input(st_input *input)
{
    GLFWwindow *window = glfwGetCurrentContext();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        input->escape = true;
        input->one_of_them = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        input->up_arrow = true;
        input->one_of_them = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        input->down_arrow = true;
        input->one_of_them = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        input->enter = true;
        input->one_of_them = true;
    }
    else{

        input->escape = false;
        input->down_arrow = false;
        input->up_arrow = false;
        input->enter = false;
        input->one_of_them = false;
    }

}