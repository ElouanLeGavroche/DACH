#ifndef COUNTRY
#define COUNTRY

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#include "../Context/game_types.h"
#include "../../types.h"

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
int delete_tile(st_country_tile *tiles, int x, int y);

// restera dans country_.c
st_country* create_country(const st_country_map_for_render *map);
st_parsed_country* parse_country_data_for_gpu(st_country *country);
int delete_country(st_country **country);

st_country* better_load_map(const char *path);

/**
 * @brief Permet de récuperer l'indice d'un elt à partir de ces coords x et y
 */
int get_indice(int x, int y, st_country *country);
/**
 * @brief Permet de récuperer la position x et y d'un elt à partir de son indice
 */
tuple_int_duo get_position(int indice, const st_country coutry);

st_country_tile* get_tile(int x, int y, st_country *country);

#endif