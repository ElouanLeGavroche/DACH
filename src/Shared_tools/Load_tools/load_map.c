#include "../../../include/src_include/Shared_tools/Load_tools/load_map.h"

st_map* load_map(const char *path)
{
    const char *err;

    struct json_object *temp_object;
    struct json_object *json_group;
    int temp_indice, blocks_group, i, y;

    // Structures des différents éléments stocké dans le JSON
    struct json_object *root;

    struct json_object *groups;

    struct json_object *group_id;
    struct json_object *vert;
    struct json_object *frag;
    struct json_object *mesh;
    struct json_object *texture;
    
    struct json_object *blocks;
    struct json_object *_x;
    struct json_object *_y;
    struct json_object *_z;
    
    st_map *map = malloc(sizeof(st_map));
    if(!map)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return NULL;
    }

    root = json_object_from_file(PATH_FISEL_MAP);
    if(!root)
    {
        err = json_util_get_last_err();
        fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
    }
    
    // Parser la struct dans les sous structures adéquat 
    json_object_object_get_ex(root, "groups", &groups);
    if(!groups)
    {
        err = json_util_get_last_err();
        fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
    }

    temp_indice = json_object_array_length(groups);

    // Alloué à la map de quoi contenir tout les groupes
    map->nb_groups = temp_indice;

    map->groups = malloc(sizeof(st_loaded_group_map) * map->nb_groups);
    if(!map->groups)
    {
        fprintf(stderr, "Allocation échouer %s.\n", strerror(errno));
        return NULL;
    }
    
    for(y = 0; y < map->nb_groups; y ++)
    {
        st_loaded_group_map *group = &map->groups[y];
        if(!group)
        {
            fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
            return NULL;
        }

        json_group = json_object_array_get_idx(groups, y);
        if(!root)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
        }

        // Parser l'id du groupe
        group_id = json_object_object_get(json_group, "group");
        if(!root)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
        }
        group->id = json_object_get_int(group_id);

        // Parser le shader vertex
        vert = json_object_object_get(json_group, "vert");
        if(!root)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
        }
        strcpy(group->vert_shader, json_object_get_string(vert));

        // Parser le shader frag
        frag = json_object_object_get(json_group, "frag");
        if(!root)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
        }
        strcpy(group->frag_shader, json_object_get_string(frag));
        

        // Parser le mesh
        mesh = json_object_object_get(json_group, "mesh");
        if(!root)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
        }
        strcpy(group->mesh, json_object_get_string(mesh));

        // Parser la texture
        texture = json_object_object_get(json_group, "texture");
        if(!root)
        {
            err = json_util_get_last_err();
            fprintf(stderr, "Erreur lors de l'ouverture de la map : %s\n", err);
        }
        strcpy(group->texture, json_object_get_string(texture));

        blocks = json_object_object_get(json_group, "blocks");

        if (!json_object_object_get_ex(json_group, "blocks", &blocks))
            fprintf(stderr, "Le groupe de blocks n'existe pas\n");
        else
        {
            
            // Récupéré le nombre de block de la liste
            blocks_group = json_object_array_length(blocks);

            // Alloué de la mémoire pour stocker tous les block du groupe
            group->tiles = malloc(sizeof(st_loaded_tile_map) * blocks_group);
            if(!group->tiles)
            {
                fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
                return NULL;
            }

            group->nb_blocks = blocks_group;

            if(group->nb_blocks)
            {
                for(i = 0; i < group->nb_blocks; i ++)
                {
                    st_loaded_tile_map *tile = &group->tiles[i];
                    
                    temp_object = json_object_array_get_idx(blocks, i);
                    _x = json_object_object_get(temp_object, "x");
                    _y = json_object_object_get(temp_object, "y");
                    _z = json_object_object_get(temp_object, "z");
                    
                    tile->x_indice = json_object_get_int(_x);
                    tile->y_indice = json_object_get_int(_y);
                    tile->height_value = json_object_get_int(_z);

                }
                
            }
            else
                fprintf(stderr, "Longeur incconu.\n");
        }



    }

    json_object_put(root);
    return map;
}