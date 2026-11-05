/**
 * @brief ce program à pour but de faire appel à des fonctions du code depuis le terminale lorsque l'on est en jeu.
 * Il est donc destiné au debug uniquement, et s'en tape complet des règles d'architecture, il lit ce qu'il à besoin de lire, c'est tout
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/src_include/Game/country.h"
#include "../../include/types.h"

#define STR_MAX_SIZE 256


#define KW_GET "GET "
#define KW_GET_TILE_INFO "tile_informations"

typedef char t_string[STR_MAX_SIZE];

void loop()
{
    while(1)
    {
        t_string *buffer = wait_and_read_writted();
        strcat()
        if(strcmp(buffer, ))
    }
}

t_string* wait_and_read_writted()
{
    t_string *buffer = malloc(sizeof(t_string));
    scanf("%s", buffer);
    return buffer;
}