#ifndef RENDERER
#define RENDERER

#include <stdlib.h>
#include <stdio.h>

#include "../../../extern_lib/glad/glad.h"
#include <GLFW/glfw3.h>

void view_clear();
void view_swap();
void view_close_window();
int window_should_close();
#endif