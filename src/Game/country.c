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

st_country* create_country()
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

void print_world_int_terminal(st_country country)
{
    int i, y;
    for(i = 0; i < 10; i ++)
    {
        for(y = 0; y < 10; y ++)
        {
            switch (country.tiles[i + y].type)
            {

            case GRASS:
                printf("G ");
                break;
            
            default:
                break;
            }
        }
        printf("\n");
    }
}