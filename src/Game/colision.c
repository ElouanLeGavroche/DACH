#include "../../include/src_include/Game/colision.h"

mouse_collision(st_ray ray, int map_width, int map_height)
{

    // 2. Arrondi à l'inférieur pour obtenir la case entière de la grille
    int tile_x = (int)floorf(ray.origin[0] / 2.0f);
    int tile_y = (int)floorf(ray.origin[2] / 2.0f);

   

    // 4. Conversion 2D vers votre index 1D linéaire pour le tableau
    int index_1d = tile_y * map_width + tile_x;

    printf("col : %d %d %d\n", tile_x, tile_y, index_1d);
}