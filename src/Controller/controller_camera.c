#include "../../include/src_include/Controller/controller_camera.h"

void init_camera(st_camera *camera, float speed, float near, float far, float size, float rotation)
{
    set_speed(camera, speed);
    set_near_z(camera, near);
    set_far_z(camera, far);
    set_ortho_size(camera, size);
    set_rotation(camera, rotation);
    set_ratio(camera);
    set_actual_speed(camera, 0.0f);

    camera->look = look;
    camera->camera_speed = camera_speed;

    pthread_mutex_init(&camera->mutex, NULL);
}

void init_camera_vector(st_camera *camera, vec3 pos, vec3 front, vec3 up)
{
    // On paramètre la Position de la caméra
    set_pos(camera, pos);
    // Vecteur qui correspond à ce que regarde la caméra
    set_front(camera, front);
    // Vecteur haut
    set_up(camera, up);

    glm_normalize(camera->up);
    glm_normalize(camera->front);
}

void init_camera_view(st_camera *camera)
{
    model_init_camera_view(camera);
}

void controller_set_actual_speed(st_camera *camera, float delta)
{
    set_actual_speed(camera, camera->speed * delta);
}