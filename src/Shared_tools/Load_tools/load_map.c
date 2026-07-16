#include "../../../include/src_include/Shared_tools/Load_tools/load_map.h"

void define_group(char* line)
{
    printf("coucopu\n");
}

int load_map(const char *path)
{
    FILE *file = NULL;
    char *line = NULL;

    size_t cap = 0;
    open_map(&file, path);

    st_map *map = malloc(sizeof(st_map));
    if(!map)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return FAILED_MALLOC;
    }

    // Get delim permet de récuperer chaque ligne séprarer par un ';'
    while(getdelim(&line, &cap, LOAD_MAP_SEPARATOR, file) != -1)
    {
        LM_KW_DEFINE_GROUPE;
        printf("%s", line);
        printf("\n");
        printf("\n");
    }
    printf("\n");
}

st_loaded_group_map* new_group(const char *str)
{
    st_loaded_group_map *group = malloc(sizeof(st_loaded_group_map));
    return group;
}

st_loaded_tile_map* new_tile(const char *str)
{
    st_loaded_tile_map *tile = malloc(sizeof(st_loaded_tile_map));
    return tile;
}

int open_map(FILE **file, const char *path)
{
    int err;

    *file = fopen(path, "r");
    if(!file){
        err = errno;
        fprintf(stderr, "fopen éhcoué : ");

        if(err == EACCES)
        {
            fprintf(stderr, " Le programe n'a pas la permission pour ouvrir le fichier cible.\n");
        }
        else if(err == ENOENT)
        {
            fprintf(stderr, "Fichier introuvable.\n");
            fprintf(stderr, "Chemin parcourus %s\n", path);
        }

        return -1;
    }

    return 0;
}