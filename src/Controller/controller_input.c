#include "../../include/src_include/Controller/controller_input.h"

void pressed_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    st_window_user_data *data = glfwGetWindowUserPointer(window); 
    if(data != NULL)
    {
        if(data->input != NULL)
        {
            st_input *input = data->input;
            int i;

            // Touche qui était précédamment appuyer
            bool was_down;
            // Touche appuyer
            bool is_down;

            int glfw_keys[KEY_NUM] = {
                [KEY_ESCAPE] = GLFW_KEY_ESCAPE,
                [KEY_DOWN]   = GLFW_KEY_DOWN,
                [KEY_UP]     = GLFW_KEY_UP,
                [KEY_DOWN]   = GLFW_KEY_DOWN,
                [KEY_D]      = GLFW_KEY_D,
                [KEY_Q]      = GLFW_KEY_Q,
                [KEY_S]      = GLFW_KEY_S,
                [KEY_Z]      = GLFW_KEY_Z
            };

            for(i = 0; i < KEY_NUM; i ++)
            {
                // On vérifie les entrée qui étaient enfoncée à la dernière tick
                was_down = input->down[i];
                // On regarde les touchent actuelement enfoncée
                is_down = glfwGetKey(window, glfw_keys[i]) == GLFW_PRESS;

                // Elle est appyer, mais ne l'était pas
                input->pressed[i] = is_down && !was_down;
                // Elle n'est pas appuyer, mais elle était
                input->release[i] = !is_down && was_down;
                // Est appuyer
                input->down[i] = is_down;
            }
            /*
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
                */
        }
    }
    else{
        fprintf(stderr, "Impossible de trouver les données Utilisateur pour la fenêtre Opengl : ");
        if(data == NULL)
        {
            fprintf(stderr, "La structure est null.\n");
        }
        if(data->input == NULL)
        {
            fprintf(stderr, "La structure des inputs est null.\n");
        }
        else
        {
            fprintf(stderr, "Je ne sais pas comment t'as fait ton affaire, je ne peux pas t'aider\n");
        }
    }
}