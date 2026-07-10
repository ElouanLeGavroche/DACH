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

int add_group(st_render_data *render, e_render_group_type type, int name)
{

}

void create_an_object(int name, st_mesh mesh, st_texture texture_id, st_shader shader, st_transform transform, st_mesh_group *dest)
{
    st_render_object obj;

    obj.id = name;
    obj.mesh = &mesh;
    obj.material->texture = texture_id;
    obj.material->shader = shader;
    obj.transform = transform;

    put_object_in_a_mesh_group(dest, &obj);

}

void create_a_shader(unsigned int id, st_mesh_group *dest)
{
    st_shader shader;
    shader_init(&shader, id);
    put_shader_in_mesh_group(dest, &shader);
}




// INSTANCED

void create_a_shared_shader(unsigned int id, st_mesh_group *dest)
{
    st_shader shader;
    shader_init(&shader, id);
    put_shader_in_mesh_group(dest, &shader);
}