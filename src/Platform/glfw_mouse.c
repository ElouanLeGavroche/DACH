#include "../../include/src_include/Platform/glfw_mouse.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
      st_window_user_data *data = glfwGetWindowUserPointer(window);
      st_camera *camera = data->camera;
      st_mouse *mouse = data->mouse;
      mouse->scroll_x = xoffset;
      mouse->scroll_y = yoffset;
      //mouse->scroll_y = yoffset;

      printf("%d\n", yoffset);
      glm_ortho(
            -camera->ortho_size * camera->ratio,
            camera->ortho_size * camera->ratio,
            -camera->ortho_size, camera->ortho_size, 
            -1000.0f, 
            1000.0f, 
            camera->projection
      );
}

void link_mouse(st_context *state)
{
    // Liée la strucures des entrée dans la fenêtre pour le callback
    GLFWwindow *window = glfwGetCurrentContext();
    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->mouse = &state->mouse;
    glfwSetScrollCallback(window, scroll_callback);
  
}