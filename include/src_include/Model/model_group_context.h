/***
 * @author DHENNIN Elouan
 * @date 04/07/2026
 * @paragraph Ici la gestion des groupes, éléments et shaders d'un context.
 * On peux les ajouter, les supprimer, les récupéré...
 * 
 */

#ifndef MODEL_GROUP_CONTEXT
#define MODEL_GROUP_CONTEXT

#include "../../types.h"
#include "../Config/constantes.h"

#include <string.h>

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
 * @return ERROR si echec | DONE si reussi
 */
int context_group_init(st_render_group *group, int id, e_render_group_type type);

/**
 * @brief permet d'ajouter un groupe à la liste de groupe
 * @param render structure qui contient la liste de groupe et le nombre d'elt dans celle-ci
 * @param nb le nombre d'élément à ajouter à la liste. Si 0 ou autre valeur incohérente, ce sera
 * mis automatiquement à 1
 * 
 * @return ERROR si echec | DONE si reussi
 */
int add_group(st_render_data *render, int nb, e_render_group_type type);

/**
 * @brief permet de supprimer un groupe dans la liste
 * @param groups liste des groupes
 * @param id du groupe que l'on cherche à supprimer
 * @param max la taille maximum de la liste
 * 
 * @return ERROR si echec | DONE si reussi
 */
int remove_group(st_render_group **groups, int id, int *max);

/**
 * @brief Permet de récuperer le pointeur d'un des groupe de la liste
 * @param groups la liste des groupes
 * @param id le groupe que l'on cherche à récupéré
 * @param max la taille maximum de la liste
 */
st_render_group* get_group(st_render_group *groups, int id, size_t max);

/**
 * @brief Permet de supprimer tout les group d'un context
 * @param groups la liste des groupes
 * @param nb_groups nombre de groupes
 */
int delete_groups(st_render_group *groups, int nb_groups);


/* Pour les mesh group */
// IS NULL
// IS NULL object
bool object_is_null(st_world_obj *object);
// IS NULL shader
bool shader_is_null(st_shader *shader);

// Init
// Init object
int object_init(st_world_obj *object, int id);
// Init shader
int shader_init(st_shader *shader, int id);

// Put
// Put object
int put_object_in_a_mesh_group(st_mesh_group *group, st_world_obj *object);
// Put shader
int put_shader_in_mesh_group(st_mesh_group *group, st_shader *shader);

// Remove //
// Remove object
int remove_object_of_a_group(st_world_obj **objects, int object_id, int *nb_objects);
// Remove shader
int remove_shader_of_a_group(st_shader **shaders, int object_id, int *nb_shaders);

// Delete //
// Delete object
int delete_object_list_mesh_shader(st_mesh_group *group);
// Delete shader
int delete_shader_list_mesh_group(st_mesh_group *group);

// Create //
// Create object
void create_an_object(int name, st_mesh mesh, int texture_id, float x, float y, float z, st_mesh_group *dest);
// Create shader
void create_a_shader(unsigned int id, st_mesh_group *dest);
/*                   */


/* pour les mesh instensier */
void create_a_shared_shader(unsigned int id, st_mesh_group *dest);

#endif