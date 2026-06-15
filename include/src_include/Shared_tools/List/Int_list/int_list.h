#ifndef INT_LIST
#define INT_LIST

#include <stdlib.h>
#include <stdio.h>

#include "../../../../types.h"

void init_int_lst(st_int_list **list);
void put_int_lst(st_int_list *list, int value);
void remove_int_lst(st_int_list *list, int i);
void destroy_int_lst(st_int_list *list);
void print_int_list(st_int_list *list);

st_int* get_int_lst_pointer(st_int_list *list, int i);

int get_int_lst(st_int_list *list, int i);

#endif