#include "../../../include/src_include/Shared_tools/Math/ray_casting.h"

/*
Le principe du ray casting pour faire de la détéction de collision avec la souris est : 

1. Normaliser la position de la souris dans un espace [-1.0; 1.0] grâce à la taille de la fenêtre

2. Récupéré le point visé par la caméra en x et y en multipliant la view avec la proj de la caméra

3. Tracer un vecteur sur cette axe en prenant en compte Far_z Near_z

4. Ensuite, une fois le vecteur crée, lister tout les éléments avec lesquels je veux vérifier les collisions afin de faire un test AABB
*/

void ray_casting(tuple_int_duo size_window, st_mouse mouse, st_camera camera, st_ray *res)
{
    /* Étant très nul en math, je commente tout pour être sur de comprendre et de ne pas oublié ce que j'ai fait. */

      /**********************/
     /*   Normalisation    */
    /**********************/

    /* Définir les valeurs sur lesquelles seront borner les position x et y de la souris */
    tuple_float_duo norm = {-1.0, 1.0};
    /* Normaliser la position de la souris en x et en y */
    tuple_float_duo norm_mouse_pos;

    /* Formule de normalisation (valeur - min_valeur) / (max_valeur - min_valeur) * (max_born - min_born) + min_born */
    /* Les valeurs : */
    /* valeur = pos x ou y de la souris */
    /* min_valeur & max_valeur = la taille min et max d'un axe x ou y de la fenetre : ex x = [0; 1980] */
    /* max_bord & min_bord = la taille min et max défini plus haut avec norm_value */

    float amplitude = norm.b - norm.a;

    norm_mouse_pos.a = ((mouse.pos_x) / (size_window.a) * amplitude + norm.a);
    norm_mouse_pos.b = ((size_window.b - mouse.pos_y)/ (size_window.b) * (norm.a - norm.b) + norm.b);

      /**********************/
     /*   Viseur camera    */
    /**********************/

    /* Valeur normaliser du point que vise la caméra */
    mat4 pointed_by_camera;
    glm_mat4_identity(pointed_by_camera);
    
    vec3 ray_orgin;
    vec3 ray_direction;

    /* Multiplier les deux matrices pour savoir où vont-elles*/
    glm_mat4_mul(camera.projection, camera.view, pointed_by_camera);

    /* Inverser la caméra */
    glm_mat4_inv(pointed_by_camera, pointed_by_camera);


    vec2 norm_mouse = {norm_mouse_pos.a, norm_mouse_pos.b};
    vec4 mouse_point = {norm_mouse[0], norm_mouse[1], -1.0f, 1.0f};

    vec4 world_point;
    glm_mat4_mulv(pointed_by_camera, mouse_point, world_point);

    // Récupéré les 3 premier float (x, y, z)
    glm_vec3_copy(world_point, res->origin);
    glm_vec3_copy(camera.front, res->direction);
    glm_vec3_normalize(res->direction);

    float t = camera.far_z;
    printf("%f, %f\n", norm_mouse_pos.a, norm_mouse_pos.b);

}