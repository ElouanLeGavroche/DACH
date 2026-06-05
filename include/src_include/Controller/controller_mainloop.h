#ifndef CONTROLLER_MAINLOOP
#define CONTROLLER_MAINLOOP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <math.h>
#include <time.h>

#include <pthread.h>

#include "../../type.h"
#include "../../constantes.h"

//Include du model et de la view
#include "../View/view_render_loop.h"
#include "../Model/model_mainloop.h"

void controller_mainloop_management();
void* logical_loop(void* arg);

#endif