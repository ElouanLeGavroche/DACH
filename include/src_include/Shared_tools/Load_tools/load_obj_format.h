#ifndef LOAD_OBJ_FORMAT
#define LOAD_OBJ_FORMAT

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <regex.h>

#define LINE_SIZE 30

#include "../../../../include/types.h"
void parse_line(char line[], st_tile *tile);
void load_file(char *path, st_tile *tile);

/*
Note à moi même, parser des trucs en C c'est comme se foutre un baton dans le cul, ça fait mal.
*/
#endif