#ifndef GLFW_INPUT
#define GLFW_INPUT

#include "../../types.h"
#include "../../../extern_lib/glad/glad.h"
#include "../../../extern_lib/glfw/glfw3.h"
#include <stdio.h>

void pressed_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void link_input(st_context *state);
void poll_events();

#endif