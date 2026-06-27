#include "../../include/src_include/Controller/controller_input.h"

void pressed_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    
    st_window_user_data *data = glfwGetWindowUserPointer(window); 
    st_input *input = data->input;

    if(input->ok == true)
    {
        
        pthread_mutex_lock(&input->mutex); // Verrouillage

        input->release[KEY_ESCAPE] = (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE && input->pressed[KEY_ESCAPE] == GLFW_PRESS);
        input->pressed[KEY_ESCAPE] = (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS);

        input->release[KEY_UP] = (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE && input->pressed[KEY_UP] == GLFW_PRESS);
        input->pressed[KEY_UP] = (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS);

        input->release[KEY_DOWN] = (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE && input->pressed[KEY_DOWN] == GLFW_PRESS);
        input->pressed[KEY_DOWN] = (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS);


        // Caméra
        input->release[KEY_Z] = (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE && input->pressed[KEY_Z] == GLFW_PRESS);
        input->pressed[KEY_Z] = (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS);

        input->release[KEY_Q] = (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE && input->pressed[KEY_Q] == GLFW_PRESS);
        input->pressed[KEY_Q] = (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);

        input->release[KEY_S] = (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE && input->pressed[KEY_S] == GLFW_PRESS);
        input->pressed[KEY_S] = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);

        input->release[KEY_D] = (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE && input->pressed[KEY_D] == GLFW_PRESS);
        input->pressed[KEY_D] = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);


        pthread_mutex_unlock(&input->mutex); // Déverrouillage

        // on met à jour le signal
        input->ok = false;
    }
    
}