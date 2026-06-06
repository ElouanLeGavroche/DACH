#ifndef ATOMIC_STRUCT
#define ATOMIC_STRUCT

#include <stdbool.h>
#include <stdatomic.h>

typedef struct
{
    bool escape;
}st_input;

typedef struct
{
    atomic_bool running;
}st_engine;

#endif