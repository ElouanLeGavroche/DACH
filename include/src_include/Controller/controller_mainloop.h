#ifndef CONTROLLER_MAINLOOP
#define CONTROLLER_MAINLOOP

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <math.h>
#include <time.h>

#include <pthread.h>
#include <stdatomic.h>

#include "../../type.h"
#include "../../constantes.h"

//Include du model et de la view
#include "../View/view_render_loop.h"
#include "../Model/model_mainloop.h"

#include "controller_input.h"

//Chargement des structures du jeu
#include "../../atomic_struct.h"

void controller_mainloop_management();
void* logical_loop(void *data_engine);

#endif