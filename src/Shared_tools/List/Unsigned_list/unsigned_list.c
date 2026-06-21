/**
 * @brief Ici ce trouve différente procédures qui permettent la gestion des liste de unsigned int.
 * 
 * Pourquoi ce type ?
 * 
 * Car c'est avec lui que l'on stock les VAO, VBO et EBO. Si il y en a plusieurs au sein d'un seul context,
 * cela nous permet de les afficher, les ajouter, les modifier ""aisémment"".
 */

#include "../../../../include/src_include/Shared_tools/List/Unsigned_list/unsigned_list.h"


void init_unsigned_int_lst(st_unsigned_int_list **list)
{
    *list = malloc(sizeof(st_unsigned_int_list));
    (*list)->first = NULL;
    (*list)->size = 0;

}

void put_unsigned_int_3d_obj_lst(st_unsigned_int_list *list, unsigned int value, int nb_vert, int nb_face)
{

    // Définition des variables
    st_unsigned_int *list_value = malloc(sizeof(st_unsigned_int));
    list_value->value = value;
    list_value->next = NULL;

    list_value->nb_face = nb_face;
    list_value->nb_vert = nb_vert;

    if(list->first == NULL)
    {
        list->first = list_value;
    }
    else
    {
        st_unsigned_int *tampon = list->first;

        while (tampon->next != NULL)
        {
            tampon = tampon->next;
        }
        
        tampon->next = list_value;
    }
    list->size ++;
}

void put_unsigned_int_lst(st_unsigned_int_list *list, unsigned int value)
{

    // Définition des variables
    st_unsigned_int *list_value = malloc(sizeof(st_unsigned_int));
    list_value->value = value;
    list_value->next = NULL;

    if(list->first == NULL)
    {
        list->first = list_value;
    }
    else
    {
        st_unsigned_int *tampon = list->first;

        while (tampon->next != NULL)
        {
            tampon = tampon->next;
        }
        
        tampon->next = list_value;
    }

    list->size ++;
}

st_unsigned_int* get_unsigned_int_lst_pointer(st_unsigned_int_list *list, int i)
{
    st_unsigned_int *tampon;
    if(i >= 0 && i < list->size)
    {
        tampon = list->first;

        int y;
        for(y = 0; y < i; y ++)
        {
            tampon = tampon->next;
        }
    }
    else
    {
        tampon = NULL;
    }
    return tampon;

}

unsigned int get_unsigned_int(st_unsigned_int_list *list, int i)
{
    st_unsigned_int *tampon = get_unsigned_int_lst_pointer(list, i);
    if(tampon == NULL)
    {
        printf("Vous avez demander un élément hors de la liste\n");
        tampon->value = 0;
    }
    return tampon->value;
}

void remove_unsigned_lst(st_unsigned_int_list *list, int i)
{
    if(list->first != NULL)
    {
        // Si l'on cherche à supprimer le première élément
        if (i == 0)
        {
            st_unsigned_int *tampon = list->first;
            list->first = list->first->next;

            free(tampon);

            list->size --;
        }
        else
        {
            if(get_unsigned_int_lst_pointer(list, i) == NULL)
            {
                printf("Vous avez demander un élément hors de la liste\n");
            }
            else
            {
                // On récupère le pointeur du précédent pour ne pas briser le lien
                st_unsigned_int *previous = get_unsigned_int_lst_pointer(list, i - 1);
                
                // On récupère l'acutel pour l'effacer
                st_unsigned_int *wanted = get_unsigned_int_lst_pointer(list, i);
                
                // On refait le lien entre les deux
                previous->next = wanted->next;
                
                // On efface l'élément souhaiter
                free(wanted);

                list->size --;

            }
            
        }
    }
}

void destroy_unsigned_lst(st_unsigned_int_list *list)
{
    while (list->first != NULL)
    {
        remove_unsigned_lst(list, 0);
    }

    free(list);
}