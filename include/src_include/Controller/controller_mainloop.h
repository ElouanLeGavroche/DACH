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

#include "../../types.h"
#include "../../Config/constantes.h"

//Include du model et de la view
#include "../View/view_render_loop.h"
#include "../Model/model_mainloop.h"

#include "controller_input.h"

//Chargement des structures du jeu
#include "../../types.h"


//Pages du jeu
#include "../Model/model_main_menu.h"
#include "../View/view_main_menu.h"

void controller_mainloop_management();
void* logical_loop(void *data_engine);

#endif