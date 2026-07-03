#include "../../include/src_include/Model/model_group_context.h"

bool context_group_is_null(st_group_world_obj *group)
{
    if(group == NULL)
    {
        return true;
    }
    return false;
}
/**
 * @brief Permet de mettre les valeur clean d'un context.
 * ATTENTION, il faut passer en paramètre l'ensembre du groupe, c'est qui qui se chargera
 * de le récupéré.
 */
int context_group_init(st_group_world_obj *groups, int id)
{
 
    
    if(groups == NULL)
    {
        fprintf(stderr, "Le groupe n'est pas prêt à être initialiser\n");
        return ERROR;
    }
    st_group_world_obj *group = get_group(groups, id, id);
    
    
    // Mettre les paramètre par defaut du group
    group->ID = id;
    
    /*
    Cette erreur va se déclarer si quelqu'un cherche à initialiser un group
    seul, sans liste. (il fait passer groups[i] au lieu de groups ex.)
    */
    if(group->ID != id)
    {
        fprintf(stderr, "Vous devez initialiser un groupe dans une liste, pas seul\n");
        return ERROR;
    }

    group->nb_object = 0;
    group->nb_shader = 0;

    group->objects = NULL;
    group->shaders = NULL;

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
int add_group(st_render_data *render, int nb)
{   
    int to_add = (nb == 0) ? 1 : nb;
    int i;
    int res;
    int nb_fails = 0;

    if(render->groups == NULL)
    {
        // Ajout du premier groupe au context
        render->groups = calloc(to_add, sizeof(st_group_world_obj));

        if(render->groups == NULL)
        {
            fprintf(stderr, "Erreur lors de l'allocation de la mémoir pour le groupe\n");
            return ERROR;
        }
    }
    else
    {
        st_group_world_obj *tamp = render->groups;
        render->groups = realloc(render->groups, sizeof(st_group_world_obj) * (to_add + render->nb_group));
        
        // Si l'allocation à échouer, alors on attribue le tampon qui à sauvgarder le reste 
        // De la liste. cela évite les fuite de mémoire.
        if(render->groups == NULL)
        {
            fprintf(stderr, "échec de l'agrandissement, retour à la liste de base\n");
            render->groups = tamp;
            return ERROR;
        }
    
    }     
    for(i = render->nb_group; i < (to_add + render->nb_group); i++)
    {
        res = context_group_init(render->groups, i);
        if(res == ERROR)
        {            
            // Si l'initialisation à échoué, on supprime cet éléments.
            fprintf(stderr, "L'élément à mal été initaliser\n");
            st_group_world_obj *group = render->groups;
            remove_group(&group, i, render->nb_group + to_add);
            nb_fails ++;
        }
    }
    // On y soustrait le nombre d'erreur pour ne pas fausser la liste
    render->nb_group = render->nb_group + to_add - nb_fails;
    
    return DONE;
}

int remove_group(st_group_world_obj **group, int id, size_t max)
{
    int i;
    int tamp_value;
  
    if(id > max)
    {
        fprintf(stderr, "Cet éléments n'existe pas\n");
        return ERROR;
    }
    else if(max != 0)
    {
        if(id != max)
        {
            tamp_value = (*group)[id + 1].ID;
        }
        
        for(i = id; i < max; i ++) (*group)[i] = (*group)[i + 1];

        *group = realloc(*group, sizeof(st_group_world_obj) * (max - 1));
     
        if(id != max)
        {
            if((*group)[id].ID != tamp_value)
            {
                fprintf(stderr, "Erreur lors de la suppression de l'élément.\n");
                return ERROR;
            }
        }
        max --;
    }
    else
    {
        fprintf(stderr, "Impossible de supprimer, la liste est déjà vide\n");
        return ERROR;
    }
    
    return max;
}

st_group_world_obj* get_group(st_group_world_obj *group, int id, size_t max)
{
    if(id > max)
    {
        fprintf(stderr, "Vous avez demander un group qui se trouve plus loin que la liste.\n");
        return NULL;
    }
    if(id < 0)
    {
        fprintf(stderr, "Vous ne pouvez pas supprimer un élément d'une liste dans le négative.\n");
        return NULL;
    }

    return &group[id];
}

// Partie pour les objects

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
    if(object != NULL)
    {
        fprintf(stderr, "L'object n'est pas nul, il est possible que certaines données soient perdu.\n");
        return ERROR;
    }
    
    object->ID = id;
    return DONE;
}

int put_object_in_group(st_group_world_obj *group, st_world_obj *object)
{
    if(group == NULL)
    {
        fprintf(stderr, "Le groupe n'est pas initialiser !\n");
        return ERROR;
    }
    if(object == NULL)
    {
        fprintf(stderr, "L'objet n'est pas initialiser\n");
        return ERROR;
    }

    // Pour mettre le premier élément
    if(group->nb_object == 0)
    {
        group->objects = malloc(sizeof(st_world_obj));
        if(group->objects == NULL)
        {
            fprintf(stderr, "Echec, problème avec l'attribution de l'espace mémoire pour un object dans un groupe.\n");
            return ERROR;
        }
        group->objects[0] = *object;
        if(group->objects[0].ID != object->ID)
        {
            fprintf(stderr, "Erreur lors de l'assignation de l'objet dans le groupe\n");
            return ERROR;
        }
    }
    // Pour les autres
    else
    {
        
    }
}