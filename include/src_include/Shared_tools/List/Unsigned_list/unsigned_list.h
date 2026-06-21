#ifndef UNSIGNED_LIST
#define UNSIGNED_LIST

#include <stdlib.h>
#include <stdio.h>

#include "../../../../types.h"

void init_unsigned_int_lst(st_unsigned_int_list **list);
void put_unsigned_int_3d_obj_lst(st_unsigned_int_list *list, unsigned int value, int nb_vert, int nb_face);
void put_unsigned_int_lst(st_unsigned_int_list *list, unsigned int value);
void remove_unsigned_lst(st_unsigned_int_list *list, int i);
void destroy_unsigned_lst(st_unsigned_int_list *list);


st_unsigned_int* get_unsigned_int_lst_pointer(st_unsigned_int_list *list, int i);
unsigned int get_unsigned_int(st_unsigned_int_list *list, int i);
#endif