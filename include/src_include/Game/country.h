#ifndef COUNTRY
#define COUNTRY

#include <stdio.h>
#include <stdlib.h>

#include "../../types.h"
#include "../Context/game_types.h"


typedef enum
{
    FLAT,
    NORTH,
    SOUTH,
    EAST,
    WEST
}e_type_angle;

typedef enum
{
    FREE,
    OCCUPIED
}e_cell_status;

typedef enum
{
    GRASS,
    WATER,
    FETILE
}e_tile_type;


/* À l'avenir, ils auront chacun leur fichier */

// Sera dans tile.c (pour avoir les fonction, add, replace... Je sais pas à quoi ça pourra servir, mais on sait jamais !)
st_country_tile create_tile(int angled, int type);
int delete_tile(st_country_tile **tiles, int x, int y);

// restera dans country_.c
st_country* create_country();
int delete_country();

void print_world_int_terminal(st_country country);

#endif