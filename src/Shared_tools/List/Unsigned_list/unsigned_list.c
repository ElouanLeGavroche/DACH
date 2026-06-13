/**
 * @brief Ici ce trouve différente procédures qui permettent la gestion des liste de unsigned int.
 * 
 * Pourquoi ce type ?
 * 
 * Car c'est avec lui que l'on stock les VAO, VBO et EBO. Si il y en a plusieurs au sein d'un seul context,
 * cela nous permet de les afficher, les ajouter, les modifier ""aisémment"".
 */

#include "../../../../include/src_include/Shared_tools/List/Unsigned_list/unsigned_list.h"

void add_to_unsigned_list(st_unsigned_element *list, unsigned int value)
{

    // Définition des variables
    st_unsigned_element *element = malloc(sizeof(st_unsigned_element));
    st_unsigned_element *tamp = list; 
    bool in_loop = true;

    // On donne la valeur souhaiter à la nouvelle cellule de la liste
    element->elt = value;
    // On met son suivant en NULL car il n'y en à pas
    element->next = NULL;
    
    if(list->elt == -1)
    {
        list->elt = value;
        list->next = NULL;
    }
    else
    {   
        do{
            if(tamp->next == NULL)
            {
                tamp->next = element;
                
                in_loop = false;
            }
            else
            {
                tamp = tamp->next;
            }
        }while(in_loop);
    }
 
}

st_unsigned_element get_by_indice(st_unsigned_element *list, int i)
{
    int indice = 0;
    st_unsigned_element wanted_value; //= malloc(sizeof(st_unsigned_element));

    wanted_value = *list;

    while (indice != i && wanted_value.next != NULL)
    {
        
        wanted_value = *wanted_value.next;
        indice ++;
    }
    

    return wanted_value;
}

void remove_to_unsigned_list(st_unsigned_element *list)
{

}