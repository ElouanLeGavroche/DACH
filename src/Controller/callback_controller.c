#include "../../include/src_include/Controller/callback_controller.h"

void resize_cam(st_window_user_data *data)
{
      st_loaded_windows_data *window_parametr = data->window;
      st_camera *camera = data->camera;
    //glFrustum(cx-halfWidth*aspect, cx+halfWidth*aspect, bottom, top, zNear, zFar);

      // Calcule du ration pour la projection : 
      //float aspect = ((float)window_parametr->size_x / (float)window_parametr->size_y);
      float aspect = 1*(window_parametr->size_x / window_parametr->size_y);
      float half_height = camera->ortho_size;
      float half_widht = half_height * aspect;

      glm_ortho(
            half_widht , half_widht,
            -camera->ortho_size, camera->ortho_size, 
            -camera->near_z, 
            camera->far_z, 
            camera->projection
      );
      printf("%f, %f, %f\n", half_widht, half_height, camera->ortho_size);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
      st_window_user_data *data = glfwGetWindowUserPointer(window);
      st_camera *camera = data->camera;
      st_loaded_windows_data *window_parametr = data->window;

      printf("%f\n", camera->ortho_size);
      if(camera->ortho_size >= 3.0f && camera->ortho_size <= 25.0f)
            camera->ortho_size -= yoffset;
      if(camera->ortho_size <= 3.0f)
            camera->ortho_size = 3.0f;
      if(camera->ortho_size >= 25.0f)
            camera->ortho_size = 25.0f;
      
      //resize_cam(data);
      //glm_perspective(glm_rad(camera->ratio), (float)1280/(float)720, 0.1f, 100.0f, camera->projection);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){

      st_window_user_data *data = glfwGetWindowUserPointer(window);
      st_loaded_windows_data *window_parametr = data->window;

      glViewport(0, 0, width, height);

      window_parametr->size_x = width;
      window_parametr->size_y = height;


      //resize_cam(data);

}