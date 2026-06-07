#ifndef MODEL_INIT
#define MODEL_INIT

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <json-c/json.h> 

#include "../../types.h"
#include "../Config/constantes.h"

// Outil de stack qu'il faut ajouter à l'engine lors de l'initialisation
#include "../Model/model_stack.h"

#define DEFAULT_READ_SIZE 1
#define READ_SIZE 4
#define NB_DATA_TO_LOAD_FOR_SCREEN 3

int load_screen_data(st_loaded_windows_data *screen_data, st_engine *engine_state);

#endif