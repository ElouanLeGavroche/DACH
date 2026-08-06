#include "../../include/src_include/Platform/glfw_mouse.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
      st_window_user_data *data = glfwGetWindowUserPointer(window);
      st_camera *camera = data->camera;

      printf("%f\n", camera->ortho_size);
      if(camera->ortho_size >= 3.0f && camera->ortho_size <= 25.0f)
            camera->ortho_size -= yoffset;
      if(camera->ortho_size <= 3.0f)
            camera->ortho_size = 3.0f;
      if(camera->ortho_size >= 25.0f)
            camera->ortho_size = 25.0f;
      
      glm_ortho(
            -camera->ortho_size * camera->ratio,
            camera->ortho_size * camera->ratio,
            -camera->ortho_size, camera->ortho_size, 
            -1000.0f, 
            1000.0f, 
            camera->projection
      );
}
void new_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
      st_window_user_data *data = glfwGetWindowUserPointer(window);
      st_mouse *mouse = data->mouse;

      mouse->scroll_x = xoffset;
      mouse->scroll_y = yoffset;
}
void link_mouse(st_context *state)
{
    // Liée la strucures des entrée dans la fenêtre pour le callback
    GLFWwindow *window = glfwGetCurrentContext();
    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->input = &state->inputs;
    data->mouse = &state->mouse;
    glfwSetScrollCallback(window, new_scroll_callback);
  
}