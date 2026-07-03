#ifndef GAME_TYPES
#define GAMEE_TYPES

#include "../../types.h"
/**
 * @brief ici le développeur doit indiqué TOUT les context de son jeu.
 * En sachant que le premier sera celui qui sera charger... En premier.
 */
#ifndef context_list
#define context_list
typedef enum e_context_list{
    C_NONE,
    C_BACK,

    C_MAIN_MENU,
    C_GAME,

    C_NUM
} e_context_list;
#endif

extern st_state main_menu_state;
extern st_state game_state;

#endif