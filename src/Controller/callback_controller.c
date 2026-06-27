#include "../../include/src_include/Controller/callback_controller.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  st_window_user_data *data = glfwGetWindowUserPointer(window);
  st_camera *camera = data->camera;
  
  printf("%f\n", camera->fov);
  if(camera->fov >= 1.0f && camera->fov <= 45.0f)
        camera->fov -= yoffset;
  if(camera->fov <= 1.0f)
        camera->fov = 1.0f;
  if(camera->fov >= 45.0f)
        camera->fov = 45.0f;

  glm_perspective(glm_rad(camera->fov), (float)1280/(float)720, 0.1f, 100.0f, camera->projection);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}