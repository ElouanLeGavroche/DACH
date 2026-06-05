#ifndef MODEL_MAINLOOP
#define MODEL_MAINLOOP

#include <stdlib.h>
#include <stdbool.h>

#include <math.h>
#include <time.h>

#include "../../constantes.h"

void wait_frame(struct timespec time_a, struct timespec time_b);
void wait_tick(struct timespec time_a, struct timespec time_b);

double calculus_elapsed_time(struct timespec time_a, struct timespec time_b);

void wait_time(struct timespec time_a, struct timespec time_b, double elapsed, double time);

#endif