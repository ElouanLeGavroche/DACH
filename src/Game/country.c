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

int delete_tile(st_country_tile *tiles, int x, int y)
{
    int i;

    free(&tiles[x + y]);
    for(i = x+ y; i < 100; i ++) {tiles[i] = tiles[i + 1];}

    tiles = realloc(tiles, sizeof(st_country_tile));

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

    x = (x < country->min_x || x > country->size_x)? -1 : x;
    y = (y < country->min_y || x > country->size_y)? -1 : y;
    
    return (x == -1 || y == -1)? -1 : ((x * country->size_x + 1) * y);
}

int realloc_country_size(st_country *country, size_t n_size)
{
    if(!country)
    {
        fprintf(stderr, "Impossible de realloc country : il est null.\n");
        return -1;
    }
    
    st_country_tile *temp = realloc(country->tiles, n_size);
    if (!temp) 
    {
        free(country->tiles);
        fprintf(stderr, "Allocation échouée : %s\n", strerror(errno));
        return RES_FAILED_MALLOC;
    }
    country->tiles = temp;

    printf("Avé\n");
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
    /* Déclaration des variables */
    
    // Permet de récupéré les erreur lié à Json
    const char *err;

    // Variable temporaire ou d'indice
    int temp_indice, i, j;
    
    // Variable min max pour définir des tailles de variables
    int max_x = INT_MIN;
    int max_y = INT_MIN;
    int min_x = INT_MAX;
    int min_y = INT_MAX; 
    int total = 0;

    // Variables Json
    struct json_object *root;

    struct json_object *blocks;
    struct json_object *block;
    struct json_object *_type;
    struct json_object *_x;
    struct json_object *_y;
    struct json_object *_z;
    struct json_object *_angle;

    // Variable qui sera entrer dans les tiles
    int x;
    int y;
    int angle;
    int type;
    float z;

    /* initialisation de country */
    st_country *country = malloc(sizeof(st_country));
    if(!country)
    {
        fprintf(stderr, "Allocation de country échouer : %s\n", strerror(errno));
        return NULL;
    }
    country->size_x = INT_MIN;
    country->size_y = INT_MIN;
    country->min_x = INT_MAX;
    country->min_y = INT_MAX;

    /* Chargement du fichier */
    root = json_object_from_file(path);
    if(!root)
    {
        err = json_util_get_last_err();
        fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
        return NULL;
    }

    /* Mettre les blocs dans une liste */
    json_object_object_get_ex(root, "blocks", &blocks);
    if(!blocks)
    {
        err = json_util_get_last_err();
        fprintf(stderr, "Erreur lors de la récupération des datas de la map : %s\n", err);
        return NULL;
    }

    /* Récuperer la taille de la liste */
    temp_indice = json_object_array_length(blocks);
    
    /* Looper une première fois dans la liste pour définir les dimensions de la carte */
    for(i = 0; i < temp_indice; i ++)
    {
        /* Récuperer un bloc */
        block = json_object_array_get_idx(blocks, i);
        if(!block)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération du bloc : %s\n", err);
            return NULL;
        }

        /* Récuperer ça valeur X */
        _x = json_object_object_get(block, "x");
        if(!_x)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération de la pos x : %s\n", err);
            return NULL;
        }

        /* Récuperer ça valeur Y */
        _y = json_object_object_get(block, "y");
        if(!_y)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération de la pos y : %s\n", err);
            return NULL;
        }

        /* Donner les valeur x et y à des varibles à type natif */
        x = json_object_get_int(_x);
        y = json_object_get_int(_y);

        /* Vérification des min et max */
        if(x > max_x){ max_x = x; }
        if(y > max_y){ max_y = y; }

        if(x < min_x){ min_x = x; }
        if(y < min_y){ min_y = y; }
    }
    
    /* Définir la taille de la carte */
    /* Notez que l'on enregistre avec ça, des blocs qui n'existe pas : */
    /*
        Si un monde à des trou, le jeu le remplira avec des cases vide
        qui existe d'un point de vue logique.
    */
    total = max_x * max_y;

    // Alloué à la map de quoi contenir tout les blocks
    country->tiles = malloc(sizeof(st_country_tile) * total);  
    if(!country->tiles)
    {
        fprintf(stderr, "Allocation des tiles échouer %s.\n", strerror(errno));
        return NULL;
    }

    /* Enregistrer les données dans la structure */
    country->size_x = max_x;
    country->size_y = max_y;

    country->min_x = min_x;
    country->min_y = min_y;

    /* à faire : boucle pour définir tout les blocs comme vide */

    /* Seconde boucle pour crée les blocs qui existe */
    for(i = 0; i < temp_indice; i ++)
    {
        /* On récupère un bloc */
        block = json_object_array_get_idx(blocks, i);
        if(!block)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération du bloc : %s\n", err);
            return NULL;
        }
        
        /* On récupère le type du bloc */
        _type = json_object_object_get(block, "t");
        if(!_type)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération du type : %s\n", err);
            return NULL;
        }

        /* On récupère ça coordonnée X */
        _x = json_object_object_get(block, "x");
        if(!_x)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération de la pos x : %s\n", err);
            return NULL;
        }

        /* On récupère ça coordonnée y */
        _y = json_object_object_get(block, "y");
        if(!_y)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération de la pos y : %s\n", err);
            return NULL;
        }

        /* On récupère ça coordonnée Z */
        _z = json_object_object_get(block, "z");
        if(!_z)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération de la pos z : %s\n", err);
            return NULL;
        }

        /* On récupère sont angle (s'il est incliné vert rien/nord/sud/est...) */
        _angle = json_object_object_get(block, "angle");
        if(!_angle)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de la récupération de la pos z : %s\n", err);
            return NULL;
        }

        /* On envoie ces valeur dans des variables typé natif */
        x = json_object_get_int(_x);
        y = json_object_get_int(_y);
        /* Petit calcule pour que une hauteur de 1 soit à la bonne taille */
        z = (float)json_object_get_int(_z) / 2.5;
        angle = json_object_get_int(_angle);
        type = json_object_get_int(_type);

        /* On envoie tout ça dans la structure */
        country->tiles[get_indice(x, y, country)].type = type;
        country->tiles[get_indice(x, y, country)].angled = angle;
        country->tiles[get_indice(x, y, country)].height = z;
    }

    /* Loop pour print le monde (debug)*/
    for(i = country->min_x; i <= country->size_x; i ++)
    {
        for(j = country->min_y; j <= country->size_y; j ++)
        {
            printf("x : %d | y : %d | res : %d\n", i, j, country->tiles[get_indice(i, y, country)].type);
        }
        printf("\n");
        
    }

    /* Libération de la mémoire des éléments qui ne sont plus utiles*/
    json_object_put(root);
    return country;
}