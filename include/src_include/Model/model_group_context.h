#ifndef MODEL_GROUP_CONTEXT
#define MODEL_GROUP_CONTEXT

#include "../../types.h"
#include "../Config/constantes.h"

#include <string.h>

int context_group_is_null(st_group_world_obj *group);
int context_group_init(st_group_world_obj *groups, int nb);
int add_group(st_render_data *render, int nb);
int remove_group(st_group_world_obj **group, int id, size_t max);

st_group_world_obj* get_group(st_group_world_obj *group, int id, size_t max);

#endif