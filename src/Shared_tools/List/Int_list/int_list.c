#include "../../../../include/src_include/Shared_tools/List/Int_list/int_list.h"
/**
 * @brief Permet d'initialiser une liste d'entier.
 */
void init_int_lst(st_int_list **list)
{
    *list = malloc(sizeof(st_int_list));
    (*list)->first = NULL;
    (*list)->size = 0;
}


/**
 * @brief Insert à la fin d'une liste d'entier une nouvelle valeur.
 */
void put_int_lst(st_int_list *list, int value)
{

    // Définition des variables
    st_int *list_value = malloc(sizeof(st_int));
    list_value->value = value;
    list_value->next = NULL;

    if(list->first == NULL)
    {
        list->first = list_value;
    }
    else
    {
        st_int *tampon = list->first;

        while (tampon->next != NULL)
        {
            tampon = tampon->next;
        }
        
        tampon->next = list_value;
    }

    list->size ++;
 
}

/** 
 * @brief Récupère le pointeur d'une liste d'entier à l'adresse i. Utile pour la 
 * destruction de la liste ou la suppression d'un elt de celle-ci.
 */
st_int* get_int_lst_pointer(st_int_list *list, int i)
{
    st_int *tampon;
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

/**
 * @brief Récupère la valeur int d'une liste de flotant à l'indice i.
 */
int get_int_lst(st_int_list *list, int i)
{
    st_int *tampon = get_int_lst_pointer(list, i);
    if(tampon == NULL)
    {
        printf("Vous avez demander un élément hors de la liste\n");
    }
    return tampon->value;
}

/**
 * @brief Supprime un valeur par sont indice 
 */
void remove_int_lst(st_int_list *list, int i)
{
    // Si l'on cherche à supprimer le première élément
    if (i == 0)
    {
        st_int *tampon = list->first;
        list->first = list->first->next;

        free(tampon);

        list->size --;
    }
    else
    {
        if(get_int_lst_pointer(list, i) == NULL)
        {
            printf("Vous avez demander un élément hors de la liste\n");
        }
        else
        {
            // On récupère le pointeur du précédent pour ne pas briser le lien
            st_int *previous = get_int_lst_pointer(list, i - 1);
            
            // On récupère l'acutel pour l'effacer
            st_int *wanted = get_int_lst_pointer(list, i);
            
            // On refait le lien entre les deux
            previous->next = wanted->next;
            
            // On efface l'élément souhaiter
            free(wanted);

            list->size --;

        }
        
    }
    
}

/**
 * @brief Détruit l'instanec de l'objet.
 */
void destroy_int_lst(st_int_list *list)
{
    
    while (list->first != NULL)
    {
        remove_int_lst(list, 0);
    }

    free(list);
    
}

/**
 * @brief Affiche la liste.
 */
void print_int_list(st_int_list *list)
{
    int i;
    st_int *tampon = list->first;

    for(i = 0; i < list->size; i ++)
    {
        printf("%d ", tampon->value);
        tampon = tampon->next;
    }
    printf("\n");
}


int get_int_list_size(st_int_list *list)
{
    return list->size;
}
