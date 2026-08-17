#include "../../include/src_include/Core/context_group.h"

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
    group->data = NULL;

    group->tables = malloc(sizeof(vt_group_virtual_table));
    if (!group->tables) {
        fprintf(stderr, "Allocation échouée : %s\n", strerror(errno));
        return RES_FAILED_MALLOC;
    }

    group->tables->add_element = NULL;
    group->tables->remove_element = NULL;
    group->tables->get_element = NULL;

    // Création du type de groupe
    switch (group->type)
    {
    case RENDER_GROUP_MESH:
        // Déclarer le pointeur
        group->data = malloc(sizeof(st_mesh_group));
        if (!group->data) {
            fprintf(stderr, "Allocation échouée : %s\n", strerror(errno));
            return RES_FAILED_MALLOC;
        }
        st_mesh_group *normal_type = group->data;

        // Initialiser les valeur de base de group_type
        normal_type->nb_objects = 0;
        normal_type->objects = NULL;
        // On applique les fonction correspondantes
        group->tables->add_element = add_render_mesh_object;
        group->tables->remove_element = remove_render_mesh_object;
        group->tables->get_element = get_render_mesh_group;
        break;
    
    case RENDER_GROUP_INSTANCED_MESH:
        
        // Déclarer le pointeur
        group->data = malloc(sizeof(st_instanced_mesh_group));
        if (!group->data) {
            fprintf(stderr, "Allocation échouée : %s\n", strerror(errno));
            return RES_FAILED_MALLOC;
        }
        st_instanced_mesh_group *instanced_type = (st_instanced_mesh_group*)group->data;;


        // Initialiser les valeur de base de group_type
        instanced_type->st_instanced.capacity = 0;
        instanced_type->st_instanced.count = 0;
        instanced_type->st_instanced.cpu_data = NULL;
        instanced_type->st_instanced.vbo = 0;

        instanced_type->shared_render_object = NULL;


        // On applique les fonction correspondantes
        group->tables->add_element = add_render_instenced_mesh_object;
        group->tables->remove_element = remove_render_instenced_mesh_object;
        group->tables->get_element = get_render_instenced_mesh_group;

        break;

    default:
        fprintf(stderr, "Type de groupe invalide.\n");
        return RES_ERROR;
        break;
    }

    return RES_DONE;   
}

int test_render(st_render_data *render)
{
    if(render == NULL)
    {
        fprintf(stderr, "Rendu NULL\n");
        return RES_ERROR;
    }
    if(render->groups == NULL && render->nb_groups != 0)
    {
        fprintf(stderr, "Désyncronisation entre le nombre de groupe et le pointeur.\n");
        return RES_ERROR;
    }
    if(render->nb_groups < 0)
    {
        fprintf(stderr, "Nombre de group incohérent.\n");
        return RES_ERROR;
    }
    return RES_DONE;
}

int add_group(st_render_data *render, e_render_group_type type)
{
    // Définition des variables
    int res;
    
    st_render_group *new_group = malloc(sizeof(st_render_group));
    st_render_group *temp;

    if (!new_group) {
        fprintf(stderr, "Allocation échouée : %s\n", strerror(errno));
        return RES_FAILED_MALLOC;
    }

    // Test des valeurs entrées
    if(test_render(render) == RES_ERROR)
        return RES_ERROR;
    
    // On initialise new_group
    res = context_group_init(new_group, render->nb_total_groups, type); 
    if(res != RES_DONE)
    {
        fprintf(stderr, "Echec de l'initiation du group.\n");
        return RES_ERROR;
    }
    
    // Re allouer de la place pour le nouveau groupe
    temp = realloc(render->groups, sizeof(st_render_group)* (render->nb_groups + 1));
    
    // Vérifier l'allocation
    if(!temp)
    {
        fprintf(stderr, "Erreur lors de l'allocation mémoire\n");
        return RES_ERROR;
    }
    render->groups = temp;
    
    // Allouer le nouveau group, au... groupe
    render->groups[render->nb_groups] = *new_group;
    render->nb_groups ++;
    render->nb_total_groups ++;

    free(new_group);

    return RES_DONE;

}

st_render_group* get_group(st_render_group *groups, int id, size_t max)
{
    if(groups == NULL)
    {
        fprintf(stderr, "Liste NULL\n");
        return NULL;
    }   
    size_t i = 0;
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
    int i = 0, y = 0;
    st_render_group *temp;

    while(i < render->nb_groups && render->groups[i].ID != id)
    {
        i ++;
    }

    if (i == render->nb_groups)
    {
        fprintf(stderr, "Groupe non trouvé dans la liste.\n");
        return RES_ERROR;
    }

    if(render->nb_groups == 1)
    {
        free(render->groups);
        render->groups = NULL;
        render->nb_groups = 0;
    }
    else
    {
        render->nb_groups --;
        // Faire un décalage pour "resize" la liste
        for(y = i; y < render->nb_groups; y ++) render->groups[y] = render->groups[y + 1];

        // Realocation de la liste
        temp = realloc(render->groups, sizeof(st_render_group) * render->nb_groups);

            // Vérifier l'allocation
        if(!temp)
        {
            fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
            return RES_FAILED_MALLOC;
        }
        render->groups = temp;
    }

    return RES_DONE;

}

int create_an_object(int name, st_mesh *mesh, st_texture *texture, st_shader *shader, st_transform transform, st_render_group *dest)
{
    st_render_object obj;
    int res;
    obj.material = malloc(sizeof(st_material));
    if(!obj.material)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return RES_FAILED_MALLOC;
    }

    mesh->nb_occurences ++;
    texture->nb_occurences ++;
    shader->nb_occurences ++;

    obj.id = name;

    obj.mesh = mesh;
    obj.material->texture = texture;
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
        st_instanced_mesh_group *test = (st_instanced_mesh_group*)dest->data;
        if(test->shared_render_object != NULL)
        {
            fprintf(stderr, "Vous avez déjà un mesh dans cet instance.\n");
            return RES_ERROR;
        }
        printf("Ajout d'un mesh au group d'instance.\n");
        break;
    
    default:
        fprintf(stderr, "Type de groupe invalide.\n");
        break;
    }

    
    res = generic_func_add_render_object(dest, obj);
    if(res != RES_DONE)
    {
        return RES_ERROR;
    }

    return RES_DONE;

}

int create_an_instance(int capacity, mat4 *model, st_instanced *dest)
{
    if(!dest)
    {
        fprintf(stderr, "La structure st_instanced est NULL.\n");
        return RES_ERROR;
    }
    int i;

    // Allouer les valeurs initiales
    dest->capacity = capacity;
    dest->count = capacity;
    dest->cpu_data = NULL;
    dest->vbo = 0;
    
    dest->cpu_data = malloc(sizeof(st_instance_data) * capacity);
    if(!dest->cpu_data)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return RES_FAILED_MALLOC;
    }

    // Crée les instances
    for(i = 0; i < dest->capacity; i ++)
    {
        glm_mat4_copy(model[i], dest->cpu_data[i].model);
    }  

    return RES_DONE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generic_func_add_render_object(st_render_group *group, st_render_object object)
{
    int res;

    // Vérification des données entrés
    if(group == NULL)
    {
        fprintf(stderr, "Le group passer est NULL, impossible de lui ajouter un élément.\n");
        return RES_ERROR;
    }

    res = group->tables->add_element(group->data, object);
    if(res == RES_ERROR || res == RES_FAILED_MALLOC)
    {
        return RES_ERROR;
    }

    return RES_DONE;
}

int generic_func_remove_render_object(st_render_group *group, int id)
{
    int res;
    if(group == NULL)
    {
        fprintf(stderr, "Le groupe est null, impossible de supprimer l'un de ces élément.\n");
        return RES_ERROR;
    }

    res = group->tables->remove_element(group->data, id);
    if(res == RES_ERROR || res == RES_FAILED_MALLOC)
    {
        return RES_ERROR;
    }
    return RES_DONE;
    
}

st_render_object* generic_func_get_render_object(st_render_group *group, int id)
{
    if(group == NULL)
    {
        fprintf(stderr, "Le groupe est null, impossible de récupéré l'un de ces éléments._n");
        return NULL;
    }
    st_render_object *object = group->tables->get_element(group->data, id);

    return object;
}




int add_render_mesh_object(void *void_group, st_render_object object)
{
    // Allocation de la mémoire
    st_mesh_group *object_list = (st_mesh_group *)void_group;
    st_render_object *temp;

    if(object_list == NULL)
    {
        fprintf(stderr, "La structure void group ne contient rien pour ajouter un mesh.\n");
        return RES_ERROR;
    }

    temp = realloc(object_list->objects, sizeof(st_render_object) * (object_list->nb_objects + 1));
    
    // Vérifier l'allocation
    if(!temp)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return RES_FAILED_MALLOC;
    }
    object_list->objects = temp;

    object_list->objects[object_list->nb_objects] = object;
    object_list->nb_objects ++;
    return RES_DONE;
}

int remove_render_mesh_object(void *void_group, int id)
{
    int i = 0;
    st_mesh_group *group = (st_mesh_group*)void_group;
    st_render_object *temp;

    // S'il ne reste plus rien, c'est équivalent au free
    if(group->nb_objects == 1)
    {
        free(group->objects);
        group->objects = NULL;
    }
    else
    {
        while (i < group->nb_objects && group->objects[i].id != id) i ++;
        
        if(i == group->nb_objects)
        {
            fprintf(stderr, "Element non trouvé.\n");
            return RES_ERROR;
        }

        // Loop de décalage
        for(i = i; i < group->nb_objects - 1; i ++) group->objects[i] = group->objects[i + 1];

        // Re Allocation de la nouvelle taille
        temp = realloc(group->objects, sizeof(st_render_object) * (group->nb_objects - 1));
            // Vérifier l'allocation
        if(!temp)
        {
            fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
            return RES_FAILED_MALLOC;
        }

        group->objects = temp;
    }
    
    group->nb_objects --;
    return RES_DONE;
}

st_render_object* get_render_mesh_group(void *void_group, int id)
{
    st_mesh_group *group = (st_mesh_group*)void_group;
    int i = 0;

    if(group == NULL)
    {
        fprintf(stderr, "Le groupe est null, impossible de récupéré l'un de ces éléments._n");
        return NULL;
    }

    while (i < group->nb_objects && group->objects[i].id != id) i ++;

    if(i == group->nb_objects)
    {
        fprintf(stderr, "Element non trouvé.\n");
        return NULL;
    }
    
    return &group->objects[i];
}

int add_render_instenced_mesh_object(void *void_group, st_render_object object)
{
    // Allocation mémoire
    st_instanced_mesh_group *shared_object = (st_instanced_mesh_group *)void_group;

    shared_object->shared_render_object = malloc(sizeof(st_render_object));

    // Vérifier l'allocation
    if(!shared_object->shared_render_object)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return RES_FAILED_MALLOC;
    }

    *shared_object->shared_render_object = object;
    return RES_DONE;
}

int remove_render_instenced_mesh_object(void *void_group, int)
{
    st_instanced_mesh_group *group = (st_instanced_mesh_group*)void_group;
    free(group->shared_render_object->material);
    group->shared_render_object->material = NULL;
    
    free(group->shared_render_object->mesh);
    group->shared_render_object->mesh = NULL;

    free(group->shared_render_object);
    group->shared_render_object = NULL;
    return RES_DONE;
}

st_render_object* get_render_instenced_mesh_group(void *void_group, int)
{
    st_instanced_mesh_group *group = (st_instanced_mesh_group*)void_group;
    
    if(group == NULL)
    {
        fprintf(stderr, "Le groupe est null, impossible de récupéré l'un de ces éléments._n");
        return NULL;
    }

    return group->shared_render_object;
}