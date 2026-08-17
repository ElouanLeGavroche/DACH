#ifndef CLOCK
#define CLOCK

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdbool.h>

#include <math.h>
#include <time.h>

#include "../Config/constantes.h"

void wait_frame(struct timespec time_a, struct timespec time_b);
void wait_tick(struct timespec time_a, struct timespec time_b);

double calculus_elapsed_time(struct timespec time_a, struct timespec time_b);

void wait_time(double elapsed, double time);

void get_time(struct timespec *dest);



#endif