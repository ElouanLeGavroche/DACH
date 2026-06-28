#ifndef MODEL_KEYBOARD
#define MODEL_KEYBOARD

#include <stdlib.h>
#include "../../../extern_lib/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <unistd.h>

#include "../../types.h"

void pressed_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif