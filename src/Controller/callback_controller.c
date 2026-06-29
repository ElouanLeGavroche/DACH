#include "../../include/src_include/Controller/callback_controller.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
      st_window_user_data *data = glfwGetWindowUserPointer(window);
      st_camera *camera = data->camera;
      st_loaded_windows_data *window_parametr = data->window;

      printf("%f\n", camera->fov);
      if(camera->fov >= 2.0f && camera->fov <= 25.0f)
            camera->fov -= yoffset;
      if(camera->fov <= 2.0f)
            camera->fov = 2.0f;
      if(camera->fov >= 25.0f)
            camera->fov = 25.0f;
      
      glm_ortho(
            -camera->fov - camera->ratio,
            camera->fov + camera->ratio,
            -camera->fov, camera->fov, 
            -100.0f, 
            100.0f, 
            camera->projection
      );
      //glm_perspective(glm_rad(camera->fov), (float)1280/(float)720, 0.1f, 100.0f, camera->projection);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){

      st_window_user_data *data = glfwGetWindowUserPointer(window);
      st_loaded_windows_data *window_parametr = data->window;
      st_camera *camera = data->camera;

      glViewport(0, 0, width, height);

      window_parametr->size_x = width;
      window_parametr->size_y = height;

      // Calcule du ration pour la projection : 
      camera->ratio = ((float)window_parametr->size_x / (float)window_parametr->size_y) * (4.0f / 3.0f);

      glm_ortho(
            -camera->fov - camera->ratio,
            camera->fov + camera->ratio,
            -camera->fov,
            camera->fov, 
            -100.0f, 
            100.0f, 
            camera->projection
      );
      printf("%d, %d, %f\n", window_parametr->size_x, window_parametr->size_y, camera->ratio);
}