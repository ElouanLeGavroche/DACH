#ifndef GLFW_MOUSE
#define GLFW_MOUSE

#include "../../types.h"
#include "../../../extern_lib/glad/glad.h"
#include "../../../extern_lib/glfw/glfw3.h"

#include <stdbool.h>

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void link_mouse(st_context *state);

#endif