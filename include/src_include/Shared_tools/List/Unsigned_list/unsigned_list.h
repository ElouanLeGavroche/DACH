#ifndef UNSIGNED_LIST
#define UNISIGNED_LIST

#include <stdlib.h>
#include <stdio.h>

#include "../../../../types.h"

void add_to_unsigned_list(st_unsigned_element *list, unsigned int value);
st_unsigned_element get_by_indice(st_unsigned_element *list, int i);
void remove_to_unsigned_list(st_unsigned_element *list);

#endif