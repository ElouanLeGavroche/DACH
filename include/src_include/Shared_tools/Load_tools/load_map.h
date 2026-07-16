#ifndef LOAD_MAP
#define LOAD_MAP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../../../types.h"
#include "../../Context/game_types.h"
#include "../../Config/constantes.h"

int open_map(FILE **file, const char *path);
int load_map(const char *path);

#endif