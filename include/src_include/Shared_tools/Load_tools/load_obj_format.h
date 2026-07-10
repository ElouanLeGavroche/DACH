#ifndef LOAD_OBJ_FORMAT
#define LOAD_OBJ_FORMAT

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <regex.h>

#include "../../Config/constantes.h"

#define LINE_SIZE 30

#include "../../../../include/types.h"
int parse_vertext(char line[], st_mesh_data *tile, int i_v);
int parse_face(char line[], st_mesh_data *tile, int i_f);
int load_file(char *path, st_mesh_data *tile);
int open_obj_file(FILE **file, char *path);

/*
Note à moi même, parser des trucs en C c'est comme se foutre un baton dans le cul, ça fait mal.
*/
#endif