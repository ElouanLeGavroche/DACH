#ifndef CONTEXT_REQUEST
#define CONTEXT_REQUEST

#include "context_stack.h"
#include "context_group.h"

#include "../Config/constantes.h"
#include "../../types.h"
#include "../../state.h"

void context_request(st_engine *engine_state);
void destroy_render_data(st_render_data *render);
void references_object_test(st_render_object *object);

#endif