#include "../../include/src_include/Model/model_group_context.h"

bool context_group_is_null(st_render_group *group)
{
    return (group == NULL)? true : false;
}

int context_group_init(st_render_group *group, int id, e_render_group_type type)
{
    // Vérification si le group est null ou non
    if(context_group_is_null(group))
    {
        fprintf(stderr, "Le groupe n'est pas vide.\n");
        return ERROR;
    }

    // Allocation de la mémoire pour le groupe
    group = malloc(sizeof(st_render_group));

    // Vérification de l'allocation mémoire
    if(context_group_is_null(group))
    {
        fprintf(stderr, "Echec de l'allocation mémoire pour le groupe.\n");
        return ERROR;
    }

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
        if(group_type == NULL)
        {
            fprintf(stderr, "Allocation du groupe st_mesh_group au groupe, échouer.\n");
            return ERROR;
        }

        // Ajout du pointeur dans la structure groupe
        group->data = group_type;

        // On applique les fonction correspondantes
        group->add_element = add_render_data_in_group;
        group->remove_element = remove_render_data_of_group;
        group->remove_all_elements = remove_all_render_data_of_a_group;
        group->get_element = get_render_data_of_a_group;

        group->delete_group = delete_mesh_group;

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
    }
    if(render->nb_groups < 0)
    {
        fprintf(stderr, "Nombre de group incohérent.\n");
        return ERROR;
    }
}

int add_group(st_render_data *render, e_render_group_type type)
{
    // Définition des variables
    int res;

    st_render_group *new_group;
    st_mesh_group *new_mesh_group;
    st_instanced_mesh_group *new_instanced_group;

    // Test des valeurs entrées
    if(test_render(render) == ERROR)
        return ERROR;


    // On initialise new_group
    res = context_group_init(new_group, render->nb_total_groups, type);

    // Test de l'allocation mémoire
    if(new_group == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation mémoire de new_group.\n");
        return ERROR;
    }

    switch (type)
    {
    case RENDER_GROUP_MESH:
        new_mesh_group = malloc(sizeof(st_mesh_group));

        // Test de l'allocation mémoire
        if(new_mesh_group == NULL)
        {
            fprintf(stderr, "Erreur lors de l'allocation mémoire de new_mesh_group.\n");
            return ERROR;
        }

        // Initialisation 
        new_mesh_group->nb_objects = 0;
        new_mesh_group->objects = NULL;

        break;
    
    case RENDER_GROUP_INSTANCED_MESH:
        fprintf(stderr, "Pas encore développer.\n");
        break;

    default:
        fprintf(stderr, "Type de groupe invalide.\n");
        return ERROR;
        break;
    }    

    return DONE;

}

void create_an_object(int name, st_mesh mesh, st_texture texture_id, st_shader shader, st_transform transform, st_render_group *dest)
{
    st_render_object obj;

    obj.id = name;
    obj.mesh = &mesh;
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
        if(dest->get_element == NULL)
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

    dest->add_element(dest, dest->data, obj);
    put_object_in_a_mesh_group(dest, &obj);

}