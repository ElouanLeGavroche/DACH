#ifndef CONTROLLER_INPUT
#define CONTROLLER_INPUT

#include <stdio.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "../View/view_render_loop.h"


// Charger les structure du jeu
#include "../../types.h"

void process_input(st_input *input);

#endif