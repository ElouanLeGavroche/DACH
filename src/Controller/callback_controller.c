#include "../../include/src_include/Controller/callback_controller.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
      st_window_user_data *data = glfwGetWindowUserPointer(window);
      st_camera *camera = data->camera;
      st_loaded_windows_data *window_parametr = data->window;

      printf("%f\n", camera->ortho_size);
      if(camera->ortho_size >= 2.0f && camera->ortho_size <= 25.0f)
            camera->ortho_size -= yoffset;
      if(camera->ortho_size <= 2.0f)
            camera->ortho_size = 2.0f;
      if(camera->ortho_size >= 25.0f)
            camera->ortho_size = 25.0f;
      
      glm_ortho(
            -camera->ortho_size - camera->ratio,
            camera->ortho_size + camera->ratio,
            -camera->ortho_size, camera->ortho_size, 
            -100.0f, 
            100.0f, 
            camera->projection
      );
      //glm_perspective(glm_rad(camera->ratio), (float)1280/(float)720, 0.1f, 100.0f, camera->projection);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){

      st_window_user_data *data = glfwGetWindowUserPointer(window);
      st_loaded_windows_data *window_parametr = data->window;
      st_camera *camera = data->camera;

      glViewport(0, 0, width, height);

      window_parametr->size_x = width;
      window_parametr->size_y = height;


      float cx, halfWidth = width*0.5f;
      //float aspect = (float)width/(float)height; 

    //glFrustum(cx-halfWidth*aspect, cx+halfWidth*aspect, bottom, top, zNear, zFar);

      // Calcule du ration pour la projection : 
      camera->ratio = ((float)window_parametr->size_x / (float)window_parametr->size_y) * (4.0f / 3.0f);

      glm_ortho(
            -camera->ortho_size - camera->ratio,
            camera->ortho_size + camera->ratio,
            -camera->ortho_size,
            camera->ortho_size, 
            camera->near_z, 
            camera->far_z, 
            camera->projection
      );
}