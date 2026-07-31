#ifndef GLFW_WINDOW
#define GLFW_WINDOW

#include <GLFW/glfw3.h>

#include "../Config/constantes.h"
#include "../../types.h"
#include "../../../extern_lib/glad/glad.h"

int init_window(st_loaded_windows_data *window_data);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

#endif