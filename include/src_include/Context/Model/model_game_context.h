#ifndef MODEL_GAME_CONTEXT
#define MODEL_GAME_CONTEXT

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../../../types.h"
#include "../../Config/constantes.h"
#include "../../Core/context_camera.h"
#include "../../Core/clock.h"
void update_logic_game(st_context *state);

/**
 * @brief ici l'on va définir les vecteur de position de l'instance, 
 * on va dire tel blocs se positionne où pour ensuite crée ceux-ci dans une autre fonction
 * 
 * @param amount le nombre d'instance souhaiter
 * @return liste de vecteur de position
 * 
 * @attention Devra être modifier lorsque l'on chargera des carte par des fichier
 */
mat4* init_map(int amount, st_loaded_tile_map *tiles);

/**
 * @brief Gère uniquement les déplacements de la caméra
 */
void move_camera(st_camera *camera, int dir);

/**
 * @brief Gère uniquement le zoom de la caméra
 */
void zoom_camera(st_camera *camera, st_mouse *mouse);


#endif