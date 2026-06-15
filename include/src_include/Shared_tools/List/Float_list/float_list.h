#ifndef FLOAT_LIST
#define FLOAT_LIST

#include <stdlib.h>
#include <stdio.h>

#include "../../../../types.h"

void init_float_lst(st_float_list **list);
void put_float_lst(st_float_list *list, float value);
void remove_float_lst(st_float_list *list, int i);
void destroy_float_lst(st_float_list *list);
void print_float_list(st_float_list *list);

st_float* get_float_lst_pointer(st_float_list *list, int i);

float get_float_lst(st_float_list *list, int i);

int get_float_list_size(st_float_list *list);


#endif