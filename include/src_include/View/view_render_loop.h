#ifndef VIEW_RENDER_LOOP
#define VIEW_RENDER_LOOP

#include <stdbool.h>
#include <stdio.h>

#include "../../type.h"
#include "../../constantes.h"
#include "../../../extern_lib/glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>

void view_close_window();
void view_swap();
void view_clear();
int window_should_close();

#endif