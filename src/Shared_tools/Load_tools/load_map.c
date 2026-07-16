#include "../../../include/src_include/Shared_tools/Load_tools/load_map.h"

void *define_group(char* line)
{
    printf("coucopu\n");
}

int load_map(const char *path)
{
    FILE *fp;
    char *buffer;
    size_t res;

    struct json_object *temp_object;
    struct json_object *temp_group;
    int temp_indice, temp_size, i, y;

    // Structures des différents éléments stocké dans le JSON
    struct json_object *parsed_json;
    struct json_object *groups;

    struct json_object *group_id;
    struct json_object *vert;
    struct json_object *frag;
    struct json_object *mesh;
    struct json_object *texture;
    
    struct json_object *nb_blocks;

    struct json_object *blocks;
    struct json_object *_x;
    struct json_object *_y;
    struct json_object *_z;
    

    // Variables des valeur à récuperer
    int id_value;
    const char *vert_value = NULL;
    const char *frag_value = NULL;
    const char *mesh_value = NULL;
    const char *texture_value = NULL;

    
    st_map *map = malloc(sizeof(map));
    if(!map)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return FAILED_MALLOC;
    }

    fp = fopen(PATH_LOAD_GAME_DATA, "r");
    if(fp == NULL){
        printf("Fichier non trouvé\n");
        return EXIT_FAILURE;
    }
    else{
        printf("fichier ouvert\n");
    }
printf("yoo\n");
    res = fread(buffer, 1024, 1, fp);
    printf("byte lu : %ld\n", res);
    if(res == -1)
    {
        fprintf(stderr, "Erreur lors la lecture du fichier %s\n", strerror(errno));
        return ERROR;
    }
    else
    {
        fclose(fp);
        printf("byte lu : %ld\n", res);
    }
    

    parsed_json = json_tokener_parse(buffer);

    // Parser la struct dans les sous structures adéquat 
    json_object_object_get_ex(parsed_json, "groups", &groups);
    temp_indice = json_object_array_length(groups);

    // Alloué à la map de quoi contenir tout les groupes
    map->nb_groups = temp_indice;
    map->groups = malloc(sizeof(st_loaded_group_map) * map->nb_groups);
    if(!map->groups)
    {
        fprintf(stderr, "Allocation échouer %s.\n", strerror(errno));
        return FAILED_MALLOC;
    }

    for(y = 0; y < temp_indice; y ++)
    {
        st_loaded_group_map *group = malloc(sizeof(st_loaded_group_map));
        if(!group)
        {
            fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
            return FAILED_MALLOC;
        }

        temp_group = json_object_array_get_idx(groups, i);
        
        // Parser l'id du groupe
        json_object_object_get_ex(temp_group, "group", &group_id);
        group->id = json_object_get_int(group_id);

        // Parser le shader vertex
        json_object_object_get_ex(temp_group, "vert", &vert);
        strcpy(group->vert_shader, json_object_get_string(vert));

        // Parser le shader frag
        json_object_object_get_ex(temp_group, "frag", &frag);
        strcpy(group->frag_shader, json_object_get_string(frag));

        // Parser le mesh
        json_object_object_get_ex(temp_group, "mesh", &mesh);
        strcpy(group->mesh, json_object_get_string(mesh));

        // Parser la texture
        json_object_object_get_ex(temp_group, "texture", &texture);
        strcpy(group->texture, json_object_get_string(texture));

        json_object_object_get_ex(temp_group, "blocks", &blocks);

        if(json_object_get_type(blocks) == json_type_null)
            fprintf(stderr, "Le groupe de blocks n'existe pas\n");
        else
        {
            // Récupéré le nombre de block de la liste
            temp_indice = json_object_array_length(blocks);

            // Alloué de la mémoire pour stocker tous les block du groupe
            group->tiles = malloc(sizeof(st_loaded_tile_map) * temp_indice);

            if(temp_indice)
            {
                for(i = 0; i < temp_indice; i ++)
                {
                    st_loaded_tile_map tile;
                    
                    temp_object = json_object_array_get_idx(blocks, i);
                    _x = json_object_object_get(temp_object, "x");
                    _y = json_object_object_get(temp_object, "y");
                    _z = json_object_object_get(temp_object, "z");

                    tile.x_indice = json_object_get_int(_x);
                    tile.y_indice = json_object_get_int(_y);
                    tile.height_value = json_object_get_int(_z);

                    group->tiles[i] = tile;
                }
                
            }
            else
                fprintf(stderr, "Longeur incconu.\n");
        }

        map->groups[i] = *group;
    }

    

    /*
    size_x_value = json_object_get_int(size_x);
    size_y_value = json_object_get_int(size_y);
    frame_rate_value = json_object_get_int(frame_rate);
    */
}