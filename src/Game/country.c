#include "../../include/src_include/Game/country.h"

st_country_tile create_tile(int angled, int type)
{
    st_country_tile tile;

    tile.type = type;   
    tile.angled = angled;
    
    tile.north = FREE;
    tile.south = FREE;
    tile.east = FREE;
    tile.west = FREE;

    return tile;
}

int delete_tile(st_country_tile **tiles, int x, int y)
{
    int i;

    free(tiles[x + y]);
    for(i = x+ y; i < 100; i ++) {tiles[i] = tiles[i + 1];}

    (*tiles) = realloc((*tiles), sizeof(st_country_tile));

    return RES_DONE;
}

st_country* create_country(const st_loaded_map *map)
{
    st_country *country = malloc(sizeof(st_country));
    if(!country)
    {
        fprintf(stderr, "Erreur lors de l'allocation mémoire de country.\n");
        return NULL;
    }
    int i, y;
    for(i = 0; i < 10; i ++)
    {
        for(y = 0; y < 10; y ++)
        {
            st_country_tile tile = create_tile(FLAT, GRASS);

            st_country_tile *temp = country->tiles;
            temp = realloc(country->tiles, sizeof(st_country_tile) * (i + y + 1));
            if(!temp)
            {
                fprintf(stderr, "Erreur lors de l'allocation du pays.\n");
                return NULL;
            }
            temp[i + y] = tile;
            country->tiles = temp;
        }
    }
    
    return country;
}

int get_indice(int x, int y, st_country *country)
{
    if(!country)
    {
        fprintf(stderr, "Impossible de travailler sur country : il null.\n");
        return -1;
    }

    x = (x <= 0 && x > country->size_x)? x : -1;
    y = (y <= 0 && x > country->size_y)? y : -1;

    return (x == -1 || y == -1)? -1 : ((y * country->size_y) + x);
}

int realloc_country_size(st_country *country, size_t n_size)
{
    if(!country)
    {
        fprintf(stderr, "Impossible de realloc country : il null.\n");
        return -1;
    }

    st_country *temp = country;
    temp = realloc(country, n_size);

    if (!temp) {
        fprintf(stderr, "Allocation échouée : %s\n", strerror(errno));
        return RES_FAILED_MALLOC;
    }

    return RES_DONE;
}

st_country_tile* get_tile(int x, int y, st_country *country)
{
    if(!country)
    {
        fprintf(stderr, "Impossible de get country : il null.\n");
        return NULL;
    }
    int indice = get_indice(x, y, country);
    
    return (indice == -1)?  NULL : &country->tiles[indice];
}

st_country* better_load_map(const char *path)
{
   const char *err;

    int temp_indice, i, res;

    // Structures des différents éléments stocké dans le JSON
    struct json_object *root;

    struct json_object *blocks;
    struct json_object *block;
    struct json_object *_type;
    struct json_object *_x;
    struct json_object *_y;
    struct json_object *_z;
    struct json_object *_angle;

    int x, y, z, angle;
    
    st_country *country = malloc(sizeof(st_loaded_map));
    if(!country)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return NULL;
    }

    root = json_object_from_file(path);
    if(!root)
    {
        err = json_util_get_last_err();
        fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
        return NULL;
    }

    json_object_object_get_ex(root, "blocks", &blocks);
    if(!blocks)
    {
        err = json_util_get_last_err();
        fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
        return NULL;
    }

    temp_indice = json_object_array_length(blocks);

    // Alloué à la map de quoi contenir tout les blocks
    country->tiles = calloc(sizeof(st_country_tile), sizeof(st_country_tile) * temp_indice);  
    if(!country->tiles)
    {
        fprintf(stderr, "Allocation échouer %s.\n", strerror(errno));
        return NULL;
    }

    for(i = 0; i < temp_indice; i ++)
    {
        block = json_object_array_get_idx(blocks, i);
        if(!block)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération du bloc : %s\n", err);
            return NULL;
        }

        _type = json_object_object_get(block, "t");
        if(!_type)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération du type : %s\n", err);
            return NULL;
        }

        _x = json_object_object_get(block, "x");
        if(!_x)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération de la pos x : %s\n", err);
            return NULL;
        }

        _y = json_object_object_get(block, "y");
        if(!_x)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération de la pos y : %s\n", err);
            return NULL;
        }

        _z = json_object_object_get(block, "z");
        if(!_x)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération de la pos z : %s\n", err);
            return NULL;
        }

        _angle = json_object_object_get(block, "angle");
        if(!_angle)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération de la pos z : %s\n", err);
            return NULL;
        }

        x = json_object_get_int(_x);
        y = json_object_get_int(_y);
        z = (float)json_object_get_int(_z) / 2.5;
        angle = json_object_get_int(_angle);

        country->min_x = 0;
        country->min_y = 0;

        // Si le block est plus loin que ce qu'il est possible de faire, alors on agrandi la carte
        if(x > country->size_x || y > country->size_y)
        {
        
            country->size_x = (x > country->size_x)? x : country->size_x; 
            country->size_y = (y > country->size_y)? y : country->size_y; 
            res = realloc_country_size(country, sizeof(st_country_tile) * (country->size_x * country->size_y));
            if(res != RES_DONE)
            {
                fprintf(stderr, "Erreur lors de l'allocation mémoire de country.\n");
                return NULL;
            }
        }
        
        country->tiles[get_indice(x, y, country)].height = z;
        country->tiles[get_indice(x, y, country)].angled = angle;
        

    }
    
    return country;
}