#ifndef RESSOURCES_MANAGER
#define RESSOURCES_MANAGER

/**
 * @author Elouan DHENNIN
 * @date 04/08/2026 ébauche 
 * @date
 * 
 * 
 * @brief Système de gestion des ressources du jeu
 */

#include <stdlib.h>
#include <stdio.h>

#include "../../types.h"

#define MAX_RESSOURCES 1024

// C'est ma première marco xD
#define PRINT_TYPE(x) _Generic((x), \
    st_mesh: "st_mesh")

#define PRINT_TYPE_FOR_FAILED_MALLOC(x) _Generic((x), \
    default : "Erreur lors de l'allocation d'un type" PRINT_TYPE(x))

typedef struct st_ressources_manager
{
    void *data[MAX_RESSOURCES];
    int num;
};


#endif