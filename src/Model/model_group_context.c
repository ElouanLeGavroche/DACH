#include "../../include/src_include/Model/model_group_context.h"

bool context_group_is_null(st_render_group *group)
{
    return (group == NULL)? true : false;
}

int context_group_init(st_render_group **group, int id, e_render_group_type type)
{
    // Vérification si le group est null ou non
    if(context_group_is_null(*group))
    {
        fprintf(stderr, "Le groupe n'est pas vide.\n");
        return ERROR;
    }

    // Allocation de la mémoire pour le groupe
    *group = malloc(sizeof(st_render_group));

    // Vérification de l'allocation mémoire
    if(context_group_is_null(*group))
    {
        fprintf(stderr, "Echec de l'allocation mémoire pour le groupe.\n");
        return ERROR;
    }

    // Création de l'id
    (*group)->ID = id;

    // Application du type à la structure
    (*group)->type = type;

    // Création du type de groupe
    switch ((*group)->type)
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

        // Initialiser les valeur de base de group_type
        group_type->nb_objects = 0;
        group_type->objects = NULL;

        // Ajout du pointeur dans la structure groupe
        (*group)->data = group_type;

        // On applique les fonction correspondantes
        (*group)->add_element = add_render_data_in_group;
        (*group)->remove_element = remove_render_data_of_group;
        (*group)->remove_all_elements = remove_all_render_data_of_a_group;
        (*group)->get_element = get_render_data_of_a_group;

        (*group)->delete_group = delete_mesh_group;

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
    res = context_group_init(&new_group, render->nb_total_groups, type);

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


    // Re allouer de la place pour le nouveau groupe
    render->groups = realloc(render->groups, sizeof(st_render_group)* (render->nb_groups + 1));
    
    // Vérifier l'allocation
    if(render->groups == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation mémoire\n");
        return ERROR;
    }

    // Allouer le nouveau group, au... groupe
    render->groups[render->nb_groups] = *new_group;
    render->nb_groups ++;
    render->nb_total_groups ++;

    return DONE;

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
    if(i == max && groups[i].ID != id)
    {
        fprintf(stderr, "Élément non trouvé\n");
        return NULL;
    }
    return &groups[i];
}

int remove_group(st_render_data *render, int id)
{
    /* On va parcourir la liste pour trouver grâce à l'id, le group à supprimer */
    int i = 0;
    int res;

    while(i < render->nb_groups && render->groups[i].ID != id)
    {
        i ++;
    }
    
    if (i == render->nb_groups && render->groups[i].ID != id)
    {
        fprintf(stderr, "Groupe non trouvé dans la liste.\n");
        return ERROR;
    }
    
    // On supprime le groupe
    st_render_group * tamp = &render->groups[i];
    st_render_group ** tamptamp = &tamp;
    res = render->groups[i].delete_group(tamptamp);

    // On vérifie que la suppression c'est bien passer
    if(res == ERROR)
    {
        fprintf(stderr, "Erreur lors de la suppression du groupe.\n");
        return ERROR;
    }

    // Faire un décalage pour "resize" la liste
    for(i = i; i < render->nb_groups; i ++) render->groups[i] = render->groups[i + 1];

    render->nb_groups --;

    // Realocation de la liste
    render->groups = realloc(render->groups, sizeof(st_render_group) * render->nb_groups);
    
    // Vérifier que la réallocation c'est bien passer
    if(render->groups == NULL && render->nb_groups != 0)
    {
        fprintf(stderr, "Erreur lors de la suppression du groupe.\n");
        return ERROR;
    }

    return DONE;

}

int create_an_object(int name, st_mesh mesh, st_texture texture_id, st_shader shader, st_transform transform, st_render_group *dest)
{
    st_render_object obj;
    obj.material = malloc(sizeof(st_material));
    obj.id = name;

    obj.mesh = malloc(sizeof(st_mesh));
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
        if(dest->get_element != NULL)
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

    dest->add_element(dest, obj);

}

st_shader create_shader(unsigned int shader)
{
    st_shader t_shader;
    t_shader.shader = shader;

    return t_shader;
}

st_texture create_texture(unsigned int image)
{
    st_texture texture;
    texture.id = image;

    return texture;
}

st_transform configure_transform(st_vec3 pos, st_vec3 rotation, st_vec3 transformation)
{
    st_transform transform;
    transform.position = pos;
    transform.rotation = rotation;
    transform.transformation = transformation;

    return transform;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int add_render_data_in_group(st_render_group *group, st_render_object object)
{
    
    // Vérification des données entrés
    if(group == NULL)
    {
        fprintf(stderr, "Le group passer est NULL, impossible de lui ajouter un élément.\n");
        return ERROR;
    }

    switch (group->type)
    {
    case RENDER_GROUP_MESH:
        // Allocation de la mémoire
        st_mesh_group *object_list = group->data;
        object_list->objects = realloc(object_list->objects, sizeof(st_render_object) * (object_list->nb_objects + 1));
        
        // Vérification de l'allocation
        if(object_list->objects == NULL)
        {
            fprintf(stderr, "Allocation dans la liste échouer.\n");
            return ERROR;
        }
        
        object_list->objects[object_list->nb_objects] = object;
        object_list->nb_objects ++;
        break;
    
    default:
        break;
    }
    

    return DONE;
}

int remove_render_data_of_group(st_render_group *group)
{
    printf("remove\n");
}

int remove_all_render_data_of_a_group(st_render_group *group)
{
    printf("remove all\n");
}

st_render_object* get_render_data_of_a_group(st_render_group *group)
{
    printf("get\n");
}

int delete_mesh_group(st_render_group **group)
{   
    printf("delete\n");
}