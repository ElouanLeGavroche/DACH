/**
 * @paragraph Country.h àp plusieurs missions
 * 1. Crée, détruire, modifier les tiles
 * 2. Crée un tableau 1D à partir des données charger pour le cpu
 * 3. Parser le tableau 1D en 1D avec coord pour le préparer à être envoyé au graphisme
 * 
 * IL NE DOIS PAS SAVOIR PLUS SUR À QUOI CORRESPOND LES TEXTURE, SHADERS...
 * Ce n'est pas son job. ça c'est au controller d'en juger, il charge ce qu'il voudra
 */

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

int delete_country(st_country **country)
{
    free((*country)->tiles);
    free(*country);
}

int delete_tile(st_country_tile *tiles, int x, int y)
{
    int i;

    for(i = x+ y; i < 100; i ++) {tiles[i] = tiles[i + 1];}

    tiles = realloc(tiles, sizeof(st_country_tile));

    return RES_DONE;
}

int get_indice(int x, int y, st_country *country)
{
    if(!country)
    {
        fprintf(stderr, "Impossible de travailler sur country : il est NULL.\n");
        return -1;
    }

    x = (x < 0 || x > country->size_x)? -1 : x;
    y = (y < 0 || y > country->size_y)? -1 : y;
    
    return (x == -1 || y == -1)? -1 : ((y * country->size_x ) + x);
}

tuple_int_duo get_position(int indice, const st_country country)
{
    tuple_int_duo coords = {0, 0};

    if(indice < 0 || indice >= (country.size_x * country.size_y))
    {
        printf("Hors limite.\n");
        return (tuple_int_duo){0, 0};
    }
    coords.a = indice % country.size_x;
    coords.b = indice / country.size_y;

    return coords;

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
    st_country *country = calloc(1, sizeof(st_country));
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
    total = (max_x + 1)* (max_y + 1);
    if(total <= 0)
    {
        fprintf(stderr, "Taille de total invalide.\n");
        return NULL;
    }
    // Alloué à la map de quoi contenir tout les blocks
    country->tiles = malloc(sizeof(st_country_tile) * total);  
    if(!country->tiles)
    {
        fprintf(stderr, "Allocation des tiles échouer %s.\n", strerror(errno));
        return NULL;
    }

    /* Enregistrer les données dans la structure */
    country->size_x = max_x + 1;
    country->size_y = max_y + 1;

    country->min_x = min_x;
    country->min_y = min_y;

    /* boucle pour définir tout les blocs comme vide */
    for(i = 0; i < total; i ++)
    {
        country->tiles[i].angled = 0;
        country->tiles[i].type = 0;
        country->tiles[i].height = 0;
        
        country->tiles[i].east = NULL;
        country->tiles[i].west = NULL;
        country->tiles[i].north = NULL;
        country->tiles[i].south = NULL;
    }

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
    for(i = country->min_x; i < country->size_x; i ++)
    {
        for(j = country->min_y; j < country->size_y; j ++)
        {
            printf("x : %d | y : %d | res : %d\n", i, j, country->tiles[get_indice(i, j, country)].type);
        }
        printf("\n");
        
    }

    /* Libération de la mémoire des éléments qui ne sont plus utiles*/
    json_object_put(root);
    return country;
}


st_parsed_country* parse_country_data_for_gpu(st_country *country)
{
    if(!country)
    {
        fprintf(stderr, "Country est NULL, impossible de le parser.\n");
        return NULL;
    }
    
    st_parsed_country *country_render = malloc(sizeof(st_parsed_country));

    // Variable d'indice
    int x, y,  i, z;
    // Définition d'un type local pour les liste d'entier
    typedef int list_int;
    // Variable qui contient le nombre maximale de groupe possible
    int max_nb_group = country->size_x * country->size_y;
    // Liste des différent groupes par leur type
    list_int *list_diff_group = malloc(sizeof(list_int) * max_nb_group);
    // Nombre d'occurence des blocs par groupe
    list_int *nb_ref_per_group = malloc(sizeof(list_int)* max_nb_group);
    // Compteur du nombre de groupe
    int diff_group = 0;

    /* trouver le nombre de groupe à crée */
    for(i = 0; i < (country->size_x * country->size_y); i ++)
    {
        z = 0;
        while(z < diff_group && list_diff_group[z] != country->tiles[i].type) { z ++; }

        if(list_diff_group[z] != country->tiles[i].type)
        {
            list_diff_group[diff_group] = country->tiles[i].type;
            nb_ref_per_group[diff_group] = 0; 
            diff_group ++;
        }

        /* On calcule dès maintenant le nombre d'élément de chaque groupe */
        for(y = 0; y < diff_group; y ++)
        {
            if(list_diff_group[y] == country->tiles[i].type)
                { nb_ref_per_group[y] ++; }
        }
    }

    /* On donne le nombre de groupe à la structure */
    country_render->nb_group = diff_group;
    country_render->groups = malloc(sizeof(st_better_loaded_group_map) * country_render->nb_group);

    /* On attribue l'id, le nombre et la place correspondant à chaque groupe */
    for(i = 0; i < country_render->nb_group; i ++)
    {
        country_render->groups[i].id = list_diff_group[i];
        country_render->groups[i].nb_blocks = nb_ref_per_group[i];
        country_render->groups[i].tiles = malloc(sizeof(st_loaded_tile_map) * nb_ref_per_group[i]);
    }

    /* On parse le reste */
    int *current_index = calloc(country_render->nb_group, sizeof(int));

    for(y = 0; y < country->size_y; y ++)
    {
        for(x = 0; x < country->size_x; x ++)
        {
            st_country_tile *cpu_tile = get_tile(x, y, country);
            if(cpu_tile)
            {
                z = 0;
                while(z < country_render->nb_group && cpu_tile->type != country_render->groups[z].id) z++;
            
                if(z < country_render->nb_group)
                {
                    int idx = current_index[z];
                    country_render->groups[z].tiles[idx].height_value = cpu_tile->height;
                    country_render->groups[z].tiles[idx].x_indice = x;
                    country_render->groups[z].tiles[idx].y_indice = y;
                    current_index[z] ++;
                }
            }

            printf("Accès à x=%d, y=%d (indice=%d)\n", x, y, get_indice(x, y, country));
            
        }
        
    }

    return country_render;

}