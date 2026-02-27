#ifndef MODEL_LOAD_GAME_DATA
#define MODEL_LOAD_GAME_DATA

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <json-c/json.h> 

#include "../../type.h"
#include "../../constantes.h"

#define DEFAULT_READ_SIZE 1
#define READ_SIZE 4
#define NB_DATA_TO_LOAD_FOR_SCREEN 3

int load_screen_data(t_loaded_windows_data *screen_data);

#endif