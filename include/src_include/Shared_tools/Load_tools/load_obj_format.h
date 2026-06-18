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

#define LINE_SIZE 30

//Include des listes chainée
#include "../../Shared_tools/List/Float_list/float_list.h"
#include "../../Shared_tools/List/Int_list/int_list.h"

#include "../../../../include/types.h"
int parse_vertext(char line[], st_mesh *tile, int i_v);
int parse_face(char line[], st_mesh *tile, int i_f);
int load_file(char *path, st_mesh *tile);
int open_obj_file(FILE **file, char *path);

/*
Note à moi même, parser des trucs en C c'est comme se foutre un baton dans le cul, ça fait mal.
*/
#endif