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