#ifndef MODEL_GAME_CONTEXT
#define MODEL_GAME_CONTEXT

#include <stdio.h>
#include <errno.h>

#include "../../Config/constantes.h"
#include "../../../types.h"

void update_logic_game(st_state *state);
void init_data_game(st_state *state);

/**
 * @brief ici l'on va définir les vecteur de position de l'instance, 
 * on va dire tel blocs se positionne où pour ensuite crée ceux-ci dans une autre fonction
 * 
 * @param amount le nombre d'instance souhaiter
 * @return liste de vecteur de position
 * 
 * @attention Devra être modifier lorsque l'on chargera des carte par des fichier
 */
vec3* init_map(int amount);

void move_camera(st_camera *camera, int dir);

#endif