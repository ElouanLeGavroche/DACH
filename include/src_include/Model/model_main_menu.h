#ifndef MODEL_MAIN_MENU
#define MODEL_MAIN_MENU

#include <stdio.h>

#include "../../atomic_struct.h"

/**
 * @brief Ici se trouve le contexte de quelle touche fait quoi
 * @param input contient le tableau des touches préssées.
 */
void input_context_menu(st_engine *engine_state);

void update_logic_main_menu(st_engine *engine_state);

#endif