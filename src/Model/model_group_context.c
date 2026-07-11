#include "../../include/src_include/Model/model_group_context.h"

bool context_group_is_null(st_render_group *group)
{
    return (group == NULL)? true : false;
}

int context_group_init(st_render_group *group, int id, e_render_group_type type)
{
    // Création de l'id
    group->ID = id;

    // Application du type à la structure
    group->type = type;

    // Création du type de groupe
    switch (group->type)
    {
    case RENDER_GROUP_MESH:
        
        // Déclarer le pointeur
        st_mesh_group *group_type;
        
        // Alloué la mémoire pour le groupe
        group_type = malloc(sizeof(st_mesh_group));

        // Tester l'allocation mémoire
        if(!group_type)
        {
            fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
            return FAILED_MALLOC;
        }

        // Initialiser les valeur de base de group_type
        group_type->nb_objects = 0;
        group_type->objects = NULL;

        // Ajout du pointeur dans la structure groupe
        group->data = group_type;

        // On applique les fonction correspondantes
        group->tables->add_element = generic_func_add_render_object;
        group->tables->remove_element = generic_func_remove_render_object;
        group->tables->remove_all_elements = generic_func_remove_all_render_object;
        group->tables->get_element = generic_func_get_render_object;

        group->tables->generic_func_delete_group_object = generic_func_delete_group_object;

        break;
    
    case RENDER_GROUP_INSTANCED_MESH:
        printf("Pas encore développer.\n");
        break;

    default:
        fprintf(stderr, "Type de groupe invalide.\n");
        return ERROR;
        break;
    }

    return DONE;   
}
int test_render(st_render_data *render)
{
    if(render == NULL)
    {
        fprintf(stderr, "Rendu NULL\n");
        return ERROR;
    }
    if(render->groups == NULL && render->nb_groups != 0)
    {
        fprintf(stderr, "Désyncronisation entre le nombre de groupe et le pointeur.\n");
        return ERROR;
    }
    if(render->nb_groups < 0)
    {
        fprintf(stderr, "Nombre de group incohérent.\n");
        return ERROR;
    }
}

int add_group(st_render_data *render, e_render_group_type type)
{
    

}

st_render_group* get_group(st_render_group *groups, int id, size_t max)
{
    if(groups == NULL)
    {
        fprintf(stderr, "Liste NULL\n");
        return NULL;
    }   
    int i = 0;
    while(i < max && groups[i].ID != id)
    {
        i ++;
    }
    if(i == max)
    {
        fprintf(stderr, "Élément non trouvé\n");
        return NULL;
    }
    return &groups[i];
}

int remove_group(st_render_data *render, int id)
{
    /* On va parcourir la liste pour trouver grâce à l'id, le group à supprimer */
    int i, y = 0;
    int res;

    while(i < render->nb_groups && render->groups[i].ID != id)
    {
        i ++;
    }
    
    if (i == render->nb_groups)
    {
        fprintf(stderr, "Groupe non trouvé dans la liste.\n");
        return ERROR;
    }
    
    // On supprime le groupe
    res = render->groups[i].tables->generic_func_delete_group_object(&render->groups[i]);

    // On vérifie que la suppression c'est bien passer
    if(res == ERROR)
    {
        fprintf(stderr, "Erreur lors de la suppression du groupe.\n");
        return ERROR;
    }

    // Faire un décalage pour "resize" la liste
    for(y = i; y < render->nb_groups; y ++) render->groups[y] = render->groups[y + 1];

    render->nb_groups --;

    if(render->nb_groups == 1)
    {
        free(&render->groups[0]);
        free(render->groups);
        render->groups = 0;
        render->nb_groups = 0;
    }
    else
    {
        // Realocation de la liste
        render->groups = realloc(render->groups, sizeof(st_render_group) * render->nb_groups);

            // Vérifier l'allocation
        if(!render->groups)
        {
            fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
            return FAILED_MALLOC;
        }
    }

    return DONE;

}

int create_an_object(int name, st_mesh mesh, st_texture texture_id, st_shader shader, st_transform transform, st_render_group *dest)
{
    st_render_object obj;
    obj.material = malloc(sizeof(st_material));
    if(!obj.material)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return FAILED_MALLOC;
    }

    obj.mesh = malloc(sizeof(st_mesh));
    if(!obj.mesh)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return FAILED_MALLOC;
    }

    obj.id = name;
    *obj.mesh = mesh;
    obj.material->texture = texture_id;
    obj.material->shader = shader;
    obj.transform = transform;

    // Ici l'on vient vérifier dans quelle type on envoie l'élément
    switch (dest->type)
    {
    case RENDER_GROUP_MESH:
        // Autrement, on ajout l'élément au sein du groupe
        printf("Ajout d'un mesh au group mesh.\n");
        break;
    
    case RENDER_GROUP_INSTANCED_MESH:

        // Si la fonction ne nous retourne pas NULL, c'est qu'il y a déjà quelque chose à l'intérieur, et 
        // On ne peux pas avoir deux mesh dans un groupe d'instances.
        if(dest->tables->get_element != NULL)
        {
            fprintf(stderr, "Vous avez déjà un mesh dans cet instance.\n");
            return ERROR;
        }
        printf("Ajout d'un mesh au group d'instance.\n");
        break;
    
    default:
        fprintf(stderr, "Type de groupe invalide.\n");
        break;
    }

    dest->tables->add_element(dest, obj);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generic_func_add_render_object(st_render_group *group, st_render_object object)
{
    
    // Vérification des données entrés
    if(group == NULL)
    {
        fprintf(stderr, "Le group passer est NULL, impossible de lui ajouter un élément.\n");
        return ERROR;
    }

    group->tables->add_element(group, object);
    

    return DONE;
}

int generic_func_remove_render_object(st_mesh_group *group, int id)
{
    int i = 0;

    if(group == NULL)
    {
        fprintf(stderr, "Le groupe est null, impossible de supprimer l'un de ces élément.\n");
        return ERROR;
    }
    
    // Recherche de l'élément dans la liste.
    while (i < group->nb_objects && group->objects[i].id != id) i ++;
    
    if(i == group->nb_objects)
    {
        fprintf(stderr, "Element non trouvé.\n");
        return ERROR;
    }

      /********************************/
     // Free les info de cet élément //
    /********************************/

    /*
    note : 
        On ne supprime pas directement les ressources, car elles peuvent être partager.
        On free simplement les structure qui les relie. Ainsi l'on sais que toute les ressources
        sont encore charger quand tout est supprimer, et qu'il ne reste plus qu'à les supprimer.
        Cela comprend le shader, la texture et le mesh.
    */

    // Free du pointeur vers ses matériaux
    free(group->objects[i].material);
    // Free du pointeur vers son mesh
    free(group->objects[i].mesh);
    
    /*
    note :
        Il n'est pas nécéssaire de free l'object en lui même car c'est la liste qui possède ça mémoire.
        Lorsque l'on realloc plus bas la liste, l'élément est finalement, automatiquement oublier, et libre.
    */

    // Loop de décalage
    for(i = i; i < group->nb_objects; i ++) group->objects[i] = group->objects[i + 1];

    // S'il ne reste plus rien, c'est équivalent au free
    if(group->nb_objects - 1 == 0)
    {
        free(group->objects);
        group->objects == NULL;
    }
    else
    {
        // Re Allocation de la nouvelle taille
        group->objects = realloc(group->objects, sizeof(st_render_object) * group->nb_objects - 1);
    }

    // Vérifier l'allocation
    if(!group->objects)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return FAILED_MALLOC;
    }
    
    group->nb_objects --;
}

int generic_func_remove_all_render_object(st_mesh_group *group)
{
    int i;
    for(i = 0; i < group->nb_objects; i ++)
    {
        // Free du pointeur vers ses matériaux
        free(group->objects[i].material);
        // Free du pointeur vers son mesh
        free(group->objects[i].mesh);
    }

    free(group->objects);

    group->objects = NULL;
    group->nb_objects = 0;
}

st_render_object* generic_func_get_render_object(st_mesh_group *group, int id)
{
    int i = 0;

    if(group == NULL)
    {
        fprintf(stderr, "Le groupe est null, impossible de récupéré l'un de ces éléments._n");
        return NULL;
    }

    while (i < group->nb_objects && group->objects[i].id != id)
    {
        i ++;
    }

    if(i == group->nb_objects)
    {
        fprintf(stderr, "Element non trouvé.\n");
        return NULL;
    }

    return &group->objects[i];
}

int generic_func_delete_group_object(st_render_group *group)
{   
    
    if(group == NULL)
    {
        fprintf(stderr, "Le groupe est null, impossible de la supprimer.\n");
        return ERROR;
    }
    
    if(group->type == RENDER_GROUP_MESH)
    {
        st_mesh_group *mesh_group = (st_mesh_group *)group->data;
        generic_func_remove_all_render_object(mesh_group);
        free(group->data);
    } 
    free(group);

    printf("delete\n");
}


int _add_render_mesh_object(st_render_group *group, st_render_object object)
{
        // Allocation de la mémoire
        st_mesh_group *object_list = group->data;
        object_list->objects = realloc(object_list->objects, sizeof(st_render_object) * (object_list->nb_objects + 1));
        
        // Vérifier l'allocation
        if(!object_list->objects)
        {
            fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
            return FAILED_MALLOC;
        }
        
        object_list->objects[object_list->nb_objects] = object;
        object_list->nb_objects ++;
}

int _add_render_instenced_mesh_object(st_render_group *group, st_render_object object)
{
    // Allocation mémoire
    st_instanced_mesh_group *shared_object = group->data;
    shared_object->shared_render_object = malloc(sizeof(st_instanced_mesh_group));

    // Vérifier l'allocation
    if(!shared_object->shared_render_object)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return FAILED_MALLOC;
    }

    shared_object->shared_render_object = &object;
}