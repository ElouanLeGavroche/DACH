#include "../../include/src_include/Model/model_camera.h"

void up(st_camera *camera)
{
    // On addition la vitesse et la hauteur pour le mettre dans la position
    glm_vec3_muladds(camera->up, camera->actual_speed, camera->pos);
}

void down(st_camera *camera)
{
    // On soustrait la vitesse et la hauteur pour le mettre dans la position
    glm_vec3_mulsubs(camera->up, camera->actual_speed, camera->pos);
}

void left(st_camera *camera)
{
    vec3 res = {0};
    glm_cross(camera->front, camera->up, res);

    glm_vec3_normalize(res);
    glm_vec3_muladds(res, camera->actual_speed, camera->pos);
}

void right(st_camera *camera)
{
    vec3 res = {0};
    glm_cross(camera->front, camera->up, res);

    glm_vec3_normalize(res);
    glm_vec3_mulsubs(res, camera->actual_speed, camera->pos);
}

void rotate(st_camera *camera, float deg)
{
    pthread_mutex_lock(&camera->mutex);
    vec3 target;
    glm_vec3_copy(camera->pos, target);

    vec3 offset;

    glm_vec3_add(camera->pos, camera->front, target);

    glm_vec3_sub(camera->pos, target, offset);
    glm_vec3_rotate(offset, glm_rad(deg), camera->up);

    glm_vec3_add(target, offset, camera->pos);
    
    glm_vec3_sub(target, camera->pos, camera->front);
    glm_normalize(camera->front);
    glm_lookat(camera->pos, target, camera->up, camera->view);

    pthread_mutex_unlock(&camera->mutex);
}


void init_camera_option(st_camera *camera)
{
    // Vitesse absolue de la caméra
    camera->speed = 30.0f;
    // Vitesse relative de la caméra
    camera->actual_speed = 0.0f;
    // ortho_size de la fenêtre
    camera->ratio = ((float)SCREEN_WITH_DEFAULT / (float)SCREEN_HEIGHT_DEFAULT) * (4.0f / 3.0f);
    // Rendu le plus proche
    camera->near_z = -1000.0f;
    // Rendu le plus loin
    camera->far_z = 1000.0f; 
    // Taille du champ de vision (N 15; S 15, E 15, W 15)
    camera->ortho_size = 250.0f;
    // Valeur de l'angle de rotatio
    camera->rotation = 45.0f;

    /* On initialise la position de la caméra à une vue isométrique */
    
    // On paramètre la Position de la caméra
    glm_vec3_copy((vec3){2.0f, 2.0f, 2.0f} , camera->pos);
    // Vecteur qui correspond à ce que regarde la caméra
    glm_vec3_copy((vec3){0.450, 0.250, 0.450} , camera->front);
    // Vecteur haut
    glm_vec3_copy((vec3){0.0, 1.0, 0.0} , camera->up);

}
void init_camera_view(st_camera *camera)
{
    // Création de la vue Orthogonale avec les paramètres déclarer plus haut
    glm_ortho(
        //Champ de vue
        -camera->ortho_size * camera->ratio, 
        camera->ortho_size * camera->ratio, 
        -camera->ortho_size, 
        camera->ortho_size, 
        // Profondeur de champ
        camera->near_z, camera->far_z, 
        // Matrice de projection
        camera->projection
    );
}