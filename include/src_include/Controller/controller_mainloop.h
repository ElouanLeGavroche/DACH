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
#include "../Config/constantes.h"

// Include du model et de la view
#include "../View/view_render_loop.h"
#include "../Model/model_mainloop.h"

// Chargement des structures du jeu
#include "../../types.h"

// Système des entrées
#include "controller_input.h"

//Pages du jeu
#include "../Context/Controller/controller_main_menu_context.h"

void controller_mainloop_management(st_engine *engine_state);
void* logical_loop(void *data_engine);

void new_context(st_engine *engine_state, st_state *new_state);
void unload_data(st_engine *engine_state);
void destroy_render_data(st_render_data *render);

#endif