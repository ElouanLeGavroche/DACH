#ifndef GLFW_MOUSE
#define GLFW_MOUSE

#include "../../types.h"
#include "../../../extern_lib/glad/glad.h"
#include "../../../extern_lib/glfw/glfw3.h"

#include <stdbool.h>

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void link_mouse(st_context *state);

#endif