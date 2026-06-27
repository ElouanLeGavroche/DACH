#include "../../include/src_include/Controller/callback_controller.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  printf("sroll : %f %f\n", xoffset, yoffset);
  fflush(stdout);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}