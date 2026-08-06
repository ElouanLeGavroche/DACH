#include "../../include/src_include/Platform/glfw_mouse.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
      st_window_user_data *data = glfwGetWindowUserPointer(window);
      if(data != NULL)
      {
            if(data->mouse != NULL && data->camera != NULL)
            {
                  st_camera *camera = data->camera;
                  st_mouse *mouse = data->mouse;
                  mouse->scroll_x = xoffset;
                  if(mouse->scroll_x != 0)
                  {
                        mouse->active_scroll_x = true;
                  }

                  mouse->scroll_y = yoffset;
                  if(mouse->scroll_y != 0)
                  {
                        mouse->active_scroll_y = true;
                  }
            }
      }
      
}

void link_mouse(st_context *state)
{
    // Liée la strucures des entrée dans la fenêtre pour le callback
    GLFWwindow *window = glfwGetCurrentContext();
    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->mouse = &state->mouse;
    glfwSetScrollCallback(window, scroll_callback);
  
}