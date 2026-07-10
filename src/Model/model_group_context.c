#include "../../include/src_include/Model/model_group_context.h"

bool context_group_is_null(st_render_group *group)
{
    if(group == NULL)
    {
        return true;
    }
    return false;
}
/**
 * @brief Permet de mettre les valeur clean d'un context.
 * ATTENTION, vous devez récupéré le groupe via get_groupe au préalable !
 */
int context_group_init(st_render_group *group, int id, e_render_group_type type)
{
 
    if(group == NULL)
    {
        fprintf(stderr, "Le groupe n'est pas prêt à être initialiser\n");
        return ERROR;
    }    
    
    // Mettre les paramètre par defaut du group
    group->ID = id;
    group->type = type;
    // Ici l'on va pouvoir dire au moteur comment considéré ce groupe
    switch (type)
    {
    case RENDER_GROUP_MESH:
        st_mesh_group *rgm_data;
        group->data = rgm_data;
        break;

    case RENDER_GROUP_INSTANCED_MESH:
        st_instanced_mesh_group *rgim_data;
        group->data = rgim_data;
        break;
    
    default:
        break;
    }
    return DONE;
}

/**
 * @brief La fonction va ajouter un nouveau groupe d'éléments au context. S'il le paramètre
 * nb est rentré à NULL, il ne sera ajouter qu'un seul élément, sinon, la taille demander.
 * Exemple, si vous savez que votre context n'aura jamais plus de 5 groupes, du moins pour longtemps,
 * vous pouvez initialiser lors du add_group, 5 groupe d'un seul coup.
 * Cela évite les realloc.
 * 
 * Attention, le code ne vérifie pas si le groupe à été au préalable initier. Si d'autre valeur que NULL sont présente
 * dans les attributs de la structure, le comportement de la fonction peux-être compromis.
 * 
 * @param group La liste de groupe.
 * @param nb Le nombre de groupe à crée (Si null, il n'y en aura qu'un seul de fait).
 * 
 */
int add_group(st_render_data *render, int nb, e_render_group_type type)
{   
    // Nombre de cellule à ajouter dans la liste
    int to_add = (nb <= 0) ? ADD_CASE : nb;
    // Variable d'indice pour les liste
    int i;
    // Resultat des fonctions lancé depuis ici
    int res;
    // Calcule le nombre de fois qu'une allocation à échouer pour ajouter la vrai différence
    int nb_fails = 0;
    // Valeur tampon pour faire une backup de la liste en cas d'échec de l'agrandissement
    st_render_group *temp;

    if(render == NULL)
    {
        fprintf(stderr, "Render est null\n");
        return ERROR;
    }

    temp = render->groups;
    render->groups = realloc(render->groups, sizeof(st_render_group) * (to_add + render->nb_groups));
    
    // Si l'allocation à échouer, alors on attribue le tampon qui à sauvgarder le reste 
    // De la liste. cela évite les fuite de mémoire.
    if(render->groups == NULL)
    {
        fprintf(stderr, "échec de l'agrandissement, retour à la liste de base\n");
        render->groups = temp;
        return ERROR;
    }
         
    render->nb_groups += to_add;
    for(i = render->nb_groups - to_add; i < (render->nb_groups); i++)
    {
        res = context_group_init(&render->groups[i], i, type);
        if(res == ERROR)
        {            
            // Si l'initialisation à échoué, on supprime cet éléments.
            fprintf(stderr, "L'élément à mal été initaliser\n");
            st_render_group *group = render->groups;
            remove_group(&group, i, &render->nb_groups);
            nb_fails ++;
        }
    }
    // On y soustrait le nombre d'erreur pour ne pas fausser la liste
    render->nb_groups = render->nb_groups - nb_fails;

    // Si il y a eu des fails, on redimentionne la liste en conséquent
    if(nb_fails != 0)
    {
        render->groups = realloc(render->groups, sizeof(st_render_group) * render->nb_groups);
        
        // En cas d'échec on revient au temp précédent, et on ignore toute les modif,
        // Je considère que c'est trop la merde à ce stade xD
        if(render->groups == NULL)
        {
            fprintf(stderr, "Erreur lors du resize de la liste des groupe\n");
            render->groups = temp;
            return ERROR;
        }
    }
    
    return DONE;
}

int remove_group(st_render_group **groups, int id, int *max)
{
    int i;
    int tamp_value;
    int where = 0;
    if(*groups == NULL)
    {
        printf("Le groupe est NULL\n");
        return ERROR;
    }

    printf("ID : %d %d %d\n", (*groups)[where].ID, id, *max);
    if(*max != 1)
    {
        while((*groups)[where].ID != id && where != *max - 1)
        {
            where ++;
        }

        if(where != *max - 1)
        {
            tamp_value = (*groups)[where + 1].ID;
        }
        
        for(i = where; i < *max; i ++) (*groups)[i] = (*groups)[i + 1];

        *groups = realloc(*groups, sizeof(st_render_group) * (*max + SUB_CASE));
    
        if(id != *max - 1)
        {
            if((*groups)[where].ID != tamp_value)
            {
                fprintf(stderr, "Erreur lors de la suppression de l'élément.\n");
                return ERROR;
            }
        }
    }
    else
    {
        // On free la variable si tout est supprimer
        free(*groups);
        *groups = NULL;
        return DONE;
    }
    
    return DONE;
    
}

int delete_groups(st_render_group *groups, int nb_groups){
    int i;

    for(i = 0; i < nb_groups; i ++)
    {
        if(delete_object_list_mesh_shader(groups[i].data)  == ERROR)
        {
            fprintf(stderr, "Erreur lors de la suppression de l'élément\n");
            return ERROR;
        }
        if(delete_shader_list_mesh_group(groups[i].data) == ERROR)
        {
            fprintf(stderr, "Erreur lors de la suppression de l'élément\n");
            return ERROR;
        }
    }
    free(groups);
    return DONE;
}

st_render_group* get_group(st_render_group *groups, int id, size_t max)
{
    int where = 0;
    if(groups == NULL)
    {
        fprintf(stderr, "Liste des groupes, null\n");
        return NULL;
    }
    while(where < max && groups[where].ID != id)
    {
        where ++;
    }
    if(where == max)
    {
        fprintf(stderr, "Groupe introuvable.\n");
        return NULL;
    }

    return &groups[where];
}
  /////////////////////////////
 // Partie pour les objects //
/////////////////////////////

bool object_is_null(st_world_obj *object)
{
    if(!object)
    {
        return true;
    }
    return false;
}

int object_init(st_world_obj *object, int id)
{
    if(object == NULL)
    {
        fprintf(stderr, "L'object n'est pas nul, il est possible que certaines données soient perdu.\n");
        return ERROR;
    }
    
    object->ID = id;
    return DONE;
}


/**
 * @brief Fonction qui permet d'ajouter un élément à un group déjà défini.
 * @param group le groups seul déjà initialiser, pas la liste de groupe.
 * @param object l'objet seul, déjà initialiser.
 * @return ERROR ou DONE en fonction du résultat de l'allocation
 */
int put_object_in_a_mesh_group(st_mesh_group *group, st_world_obj *object)
{
    st_world_obj *temp;

    if(group == NULL)
    {
        fprintf(stderr, "Le groupe n'est pas initialiser !\n");
        return ERROR;
    }
    if(group->nb_objects < 0)
    {
        fprintf(stderr, "Nombre d'objets incohérents !\n");
        return ERROR;
    }
    if(object == NULL)
    {
        fprintf(stderr, "L'objet n'est pas initialiser !\n");
        return ERROR;
    }


    temp = group->objects;

    // On ajout une case mémoire
    group->objects = realloc(group->objects, (sizeof(st_world_obj) * (group->nb_objects + ADD_CASE)));
    
    // Si la reallocation à échouer, alors on revient au pointeur tampon
    if(group->objects == NULL)
    {
        group->objects = temp;
        fprintf(stderr, "Allocation mémoire à la liste object échouer, attention\n");
        return ERROR;
    }
    else
    {
        
        //L'espace mémoire est alloué, mais pas encore officialiser, donc on recherche
        //celle-ci avec un + 1 pour lui appliquer l'objet.
        
        group->objects[group->nb_objects] = *object;

        if(group->objects[group->nb_objects].ID != object->ID)
        {
            fprintf(stderr, "Erreur lors de l'insertion de la valeur dans la liste\n");                
            return ERROR;
        }
        else
        {
            // On officilise l'ajout de la valeur
            group->nb_objects ++;
        }

    }
    
    return DONE;
}

int remove_object_of_a_group(st_world_obj **objects, int object_id, int *nb_objects)
{
    int where = 0;
    int i;
    st_world_obj *temp;
    
    // Test des entrées avant suppression
    if((*objects) == NULL)
    {
        fprintf(stderr, "Le groupe passé en paramètre est soit pas initier, soit inéxistant\n");
        return ERROR;
    }
    
    // On va chercher l'objet dans la liste grâce à son ID
    while(where < *nb_objects && (*objects)[where].ID != object_id)
    {
        where ++;
    }
    if(where == *nb_objects)
    {
        fprintf(stderr, "Impossible de trouver l'objet dans la liste. Pas de suppression\n");
        return ERROR;
    }
    else
    {
        // On décale tout les éléments dans la mémoire
        for(i = where; i < *nb_objects - 1; i ++) 
            (*objects)[i] = (*objects)[i + 1];
        
        // Réallocation de la mémoire
        
        printf("next size : %ld\n", (sizeof(st_world_obj) * (*nb_objects)));
        printf("next size : %ld\n", (sizeof(st_world_obj) * (*nb_objects + SUB_CASE)));

        if(*nb_objects + SUB_CASE == 0)
        {
            free(*objects);
        }
        else
        {
            // Sauvegarde via une variable tampon
            temp = *objects;
            *objects = realloc(*objects, (sizeof(st_world_obj) * (*nb_objects + SUB_CASE)));

            if(*objects == NULL)
            {
                fprintf(stderr, "Echec de l'allocation mémoire\n");

                // On remet la valeur tampon pour récupéré les valeurs
                *objects = temp;

                // On libère tout
                *nb_objects = 0;
                
                return ERROR;
            }

            temp = NULL;
        }
        
        *nb_objects += SUB_CASE;
        
    }
    return DONE;
}

  /////////////////////////////
 // Partie pour les sharers //
/////////////////////////////

bool shader_is_null(st_shader *shader)
{
    if(!shader)
    {
        return true;
    }
    return false;
}



int shader_init(st_shader *shader, int id)
{
    if(shader == NULL)
    {
        fprintf(stderr, "L'object n'est pas nul, il est possible que certaines données soient perdu.\n");
        return ERROR;
    }
    
    shader->shader = id;
    return DONE;
}



int put_shader_in_mesh_group(st_mesh_group *group, st_shader *shader)
{
    st_shader *temp;
    
    if(group == NULL)
    {
        fprintf(stderr, "Le groupe n'est pas initialiser !\n");
        return ERROR;
    }
    if(group->nb_shaders < 0)
    {
        fprintf(stderr, "Nombre de shaders incohérents !\n");
        return ERROR;
    }
    if(shader == NULL)
    {
        fprintf(stderr, "Le shader n'est pas initialiser !\n");
        return ERROR;
    }

    temp = group->shaders;

    // On ajout une case mémoire
    group->shaders = realloc(group->shaders, sizeof(st_shader)* (group->nb_shaders + ADD_CASE));
    
    // Si la reallocation à échouer, alors on revient au pointeur tampon
    if(group->shaders == NULL)
    {
        group->shaders = temp;
        fprintf(stderr, "Allocation mémoire à la liste object échouer, attention\n");
        return ERROR;
    }
    else
    {
        
        //L'espace mémoire est alloué, mais pas encore officialiser, donc on recherche
        //celle-ci avec un + 1 pour lui appliquer l'objet.
        
        group->shaders[group->nb_shaders] = *shader;

        if(group->shaders[group->nb_shaders].shader != shader->shader)
        {
            fprintf(stderr, "Erreur lors de l'insertion de la valeur dans la liste\n");                
            return ERROR;
        }
        else
        {
            // On officilise l'ajout de la valeur
            group->nb_shaders ++;
        }

    }

    
    return DONE;
}

int delete_shader_list_mesh_group(st_mesh_group *group)
{
    if(group == NULL)
    {
        fprintf(stderr, "Vous avez rentrée un group NULL\n");
        return ERROR;
    }
    if(group->nb_shaders == 0)
    {
        fprintf(stderr, "Liste déjà vide\n");
        return ERROR;
    }

    free(group->shaders);
    group->nb_shaders = 0;
    return DONE;
}

int delete_object_list_mesh_shader(st_mesh_group *group)
{
    if(group == NULL)
    {
        fprintf(stderr, "Vous avez rentrée un group NULL\n");
        return ERROR;
    }
    if(group->nb_objects == 0)
    {
        fprintf(stderr, "Liste déjà vide\n");
        return ERROR;
    }

    free(group->objects);
    group->nb_objects = 0;
    return DONE;
}

int remove_shader_of_a_group(st_shader **shaders, int object_id, int *nb_shaders)
{
    int where = 0;
    int i;
    st_shader *temp;
    
    // Test des entrées avant suppression
    if((*shaders) == NULL)
    {
        fprintf(stderr, "Le groupe passé en paramètre est soit pas initier, soit inéxistant\n");
        return ERROR;
    }
    
    // On va chercher l'objet dans la liste grâce à son ID
    while(where < *nb_shaders && (*shaders)[where].shader != object_id)
    {
        where ++;
    }
    if(where == *nb_shaders)
    {
        fprintf(stderr, "Impossible de trouver l'objet dans la liste. Pas de suppression\n");
        return ERROR;
    }
    else
    {
        // On décale tout les éléments dans la mémoire
        for(i = where; i < *nb_shaders - 1; i ++) 
            (*shaders)[i] = (*shaders)[i + 1];
        
        // Réallocation de la mémoire
        
        printf("next size : %ld\n", (sizeof(st_shader) * (*nb_shaders)));
        printf("next size : %ld\n", (sizeof(st_shader) * (*nb_shaders + SUB_CASE)));

        if(*nb_shaders + SUB_CASE == 0)
        {
            free(*shaders);
        }
        else
        {
            // Sauvegarde via une variable tampon
            temp = *shaders;

            *shaders = realloc(*shaders, (sizeof(st_shader) * (*nb_shaders + SUB_CASE)));

            if(*shaders == NULL)
            {
                fprintf(stderr, "Echec de l'allocation mémoire\n");

                // On remet la valeur tampon pour récupéré les valeurs
                *shaders = temp;

                // On libère tout
                *nb_shaders = 0;
                
                return ERROR;
            }
        }
        
        *nb_shaders += SUB_CASE;
        
    }
    return DONE;
}

void create_an_object(int name, st_mesh mesh, int texture_id, float x, float y, float z, st_mesh_group *dest)
{
    st_world_obj obj;
    obj.mesh_obj = mesh;
    obj.texture_id = texture_id;
    obj.x_pos = x;
    obj.y_pos = y;
    obj.z_pos = z;
    
    object_init(&obj, name);

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