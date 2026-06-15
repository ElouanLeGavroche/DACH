//#include "../../../../include/src_include/Shared_tools/List/Float_list/float_list.h"
#include "../include/src_include/Shared_tools/List/Float_list/float_list.h"
/**
 * @brief Permet d'initialiser une liste de flotants.
 */
void init_float_lst(st_float_list **list)
{
    *list = malloc(sizeof(st_float_list));
    (*list)->first = NULL;
    (*list)->size = 0;
}


/**
 * @brief Insert à la fin d'une liste de flotants une nouvelle valeur.
 */
void put_float_lst(st_float_list *list, float value)
{

    // Définition des variables
    st_float *list_value = malloc(sizeof(st_float));
    list_value->value = value;
    list_value->next = NULL;

    if(list->first == NULL)
    {
        list->first = list_value;
    }
    else
    {
        st_float *tampon = list->first;

        while (tampon->next != NULL)
        {
            tampon = tampon->next;
        }
        
        tampon->next = list_value;
    }

    list->size ++;
 
}

/** 
 * @brief Récupère le pointeur d'une liste de flotants à l'adresse i. Utile pour la 
 * destruction de la liste ou la suppression d'un elt de celle-ci.
 */
st_float* get_float_lst_pointer(st_float_list *list, int i)
{
    st_float *tampon;
    if(i > 0 && i < list->size)
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
 * @brief Récupère la valeur float d'une liste de flotant à l'indice i.
 */
float get_float_lst(st_float_list *list, int i)
{
    st_float *tampon = get_float_lst_pointer(list, i);
    if(tampon == NULL)
    {
        printf("Vous avez demander un élément hors de la liste\n");
    }
    return tampon->value;
}

/**
 * @brief Supprime un valeur par sont indice 
 */
void remove_float_lst(st_float_list *list, int i)
{
    // Si l'on cherche à supprimer le première élément
    if (i == 0)
    {
        st_float *tampon = list->first;
        list->first = list->first->next;

        free(tampon);

        list->size --;
    }
    else
    {
        if(get_float_lst_pointer(list, i) == NULL)
        {
            printf("Vous avez demander un élément hors de la liste\n");
        }
        else
        {
            // On récupère le pointeur du précédent pour ne pas briser le lien
            st_float *previous = get_float_lst_pointer(list, i - 1);
            
            // On récupère l'acutel pour l'effacer
            st_float *wanted = get_float_lst_pointer(list, i);
            
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
void destroy_float_lst(st_float_list *list)
{
    
    while (list->first != NULL)
    {
        remove_float_lst(list, 0);
    }

    free(list);
    
}

/**
 * @brief Affiche la liste.
 */
void print_float_list(st_float_list *list)
{
    int i;
    st_float *tampon = list->first;

    for(i = 0; i < list->size; i ++)
    {
        printf("%f ", tampon->value);
        tampon = tampon->next;
    }
    printf("\n");
}

int main()
{
    st_float_list *list;

    init_float_lst(&list);

    put_float_lst(list, 4);
    put_float_lst(list, 6);
    put_float_lst(list, 2);
    put_float_lst(list, 8);

    print_float_list(list);

    remove_float_lst(list, 3);

    print_float_list(list);

    destroy_float_lst(list);

    return 0;
}