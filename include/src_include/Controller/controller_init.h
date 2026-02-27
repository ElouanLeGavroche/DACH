#ifndef CONTROLLER_INIT
#define CONTROLLER_INIT

#include <stdio.h>
#include <stdlib.h>

#include "../../type.h"

#include "../View/view_init.h" 
#include "../Model/model_init.h"

int controller_get_screen_data(t_loaded_windows_data *window_data);
int controller_init_graphic_lib();
int controller_init_window(t_loaded_windows_data window_data);

int controller_init();

#endif