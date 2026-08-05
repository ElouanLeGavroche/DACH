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

#define MAX_RESSOURCES 1024

typedef struct st_ressources_manager
{
    void *data[MAX_RESSOURCES];
    int num;
};


#endif