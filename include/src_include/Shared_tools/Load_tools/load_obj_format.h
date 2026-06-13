#ifndef LOAD_OBJ_FORMAT
#define LOAD_OBJ_FORMAT

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

void parse_line(char file[]);
float load_file(char *path);

#endif