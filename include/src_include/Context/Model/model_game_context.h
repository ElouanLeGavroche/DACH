#ifndef MODEL_GAME_CONTEXT
#define MODEL_GAME_CONTEXT

#include <stdio.h>

#include "../../../types.h"

void update_logic_game(st_state *state);
void init_data_game(st_state *state);

void move_camera(st_camera *camera, int dir);
void zoom_camera(st_camera *camera, float yoffset);

#endif