#ifndef UNSIGNED_LIST
#define UNISIGNED_LIST

#include <stdlib.h>
#include <stdio.h>

#include "../../../../types.h"

void put_unsigned_lst(st_unsigned_element *list, unsigned int value);
st_unsigned_element get_unsigned_lst(st_unsigned_element *list, int i);
void remove_unsigned_lst(st_unsigned_element *list);

#endif