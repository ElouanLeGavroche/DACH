#define CONTEXT_GROUP
/***
 * @author DHENNIN Elouan
 * @date 04/07/2026
 * @paragraph Ici la gestion des groupes, éléments et shaders d'un context.
 * On peux les ajouter, les supprimer, les récupéré...
 * 
 */

#ifndef CONTEXT_GROUP
#define CONTEXT_GROUP

#include "../../types.h"
#include "../Config/constantes.h"

#include <string.h>
#include <errno.h>

// Permet d'expliciter que le +1 lors de l'allocation mémoire correspond bien à
// une nouvelle case dans la mémoire de la liste.
#define ADD_CASE 1
// Permet d'expliciter le fait que l'on retire une case mémoire à la liste
#define SUB_CASE -1

/**
 * @brief return false ou true si le group entré est null ou non.
 * @param group un groupe
 * 
 * @return true si null | false si pas null
 */
bool context_group_is_null(st_render_group *group);

/**
 * @brief Permet de mettre les valeur clean d'un context.
 * ATTENTION, vous devez récupéré le groupe via get_groupe au préalable !
 * @param group un groupe
 * @param id de ce groupe
 * 
 * @return RES_ERROR si echec | RES_DONE si reussi
 */
int context_group_init(st_render_group *group, int id, e_render_group_type type);

/**
 * @brief permet de tester certaine chose dans render pour voir si les valeurs sont cohérente.
 * @param render pointeur du rendu.
 */
int test_render(st_render_data *render);

/**
 * @brief permet d'ajouter un groupe à la liste de groupe
 * @param render structure qui contient la liste de groupe et le nombre d'elt dans celle-ci
 * @param nb le nombre d'élément à ajouter à la liste. Si 0 ou autre valeur incohérente, ce sera
 * 
 * @return RES_ERROR si echec | RES_DONE si reussi
 */
int add_group(st_render_data *render, e_render_group_type type);

/**
 * @brief permet de supprimer un groupe dans la liste
 * @param groups liste des groupes
 * @param id du groupe que l'on cherche à supprimer
 * @param max la taille maximum de la liste
 * 
 * @return RES_ERROR si echec | RES_DONE si reussi
 */
int remove_group(st_render_data *render, int id);

/**
 * @brief Permet de récuperer le pointeur d'un des groupe de la liste
 * @param groups la liste des groupes
 * @param id le groupe que l'on cherche à récupéré
 * @param max la taille maximum de la liste
 */
st_render_group* get_group(st_render_group *groups, int id, size_t max);

/**
 * @brief Permet de crée un objet qui pourra se trouver dans n'importe quelle context
 * @param name identifiant de l'élément
 * @param mesh son mesh déjà crée
 * @param texture_id l'id de ça texture déjà crée
 * @param shader l'id de sont shader déjà crée
 * @param transform ces divers transformation d'un object (pos, rot, trans...)
 * @param dest group auquel est déstiné l'objet
 */
int create_an_object(int name, st_mesh *mesh, st_texture *texture, st_shader *shader, st_transform transform, st_render_group *dest);
int create_an_instance(int capacity, mat4 *positions, st_instanced *dest);

  /************************/
 /* Fonctions générique  */
/************************/

int generic_func_add_render_object(st_render_group *group, st_render_object object);
int generic_func_remove_render_object(st_render_group *group, int id);
st_render_object* generic_func_get_render_object(st_render_group *group, int id);


int add_render_mesh_object(void *void_group, st_render_object object);
int remove_render_mesh_object(void *void_group, int id);
st_render_object* get_render_mesh_group(void *void_group, int id);


int add_render_instenced_mesh_object(void *void_group, st_render_object object);
int remove_render_instenced_mesh_object(void *void_group, int);
st_render_object* get_render_instenced_mesh_group(void *void_group, int id);

#endif