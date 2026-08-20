#ifndef LOAD_MAP
#define LOAD_MAP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <json-c/json.h>

#include "../../../types.h"
#include "../../Context/game_types.h"
#include "../../Config/constantes.h"

st_country_map_for_render* load_map(const char *path);


#endif