#include "../../include/src_include/Core/context_camera.h"

void init_camera(st_camera *camera, float speed, float near, float far, float size, float rotation)
{
    set_speed(camera, speed);
    set_near_z(camera, near);
    set_far_z(camera, far);
    set_ortho_size(camera, size);
    set_rotation(camera, rotation);
    set_ratio(camera);
    set_actual_speed(camera, 1.0f);

    camera->look = look;
    camera->camera_speed = camera_speed;
    camera->update_ortho = update_ortho;

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

}


void model_init_camera_view(st_camera *camera)
{
    glm_mat4_identity(camera->projection);
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

    // Matrice de vue (view)
    vec3 target;
    glm_vec3_sub(camera->pos, camera->front, target);
    glm_lookat(camera->pos, target, camera->up, camera->view);
}

// Getters & Setters
void set_speed(st_camera *camera, float speed)
{
    camera->speed = speed;
}

void set_actual_speed(st_camera *camera, float speed)
{
    camera->actual_speed = speed;
}

void set_ratio(st_camera *camera)
{
    camera->ratio = ((float)1980 / (float)1080) * (4.0f / 3.0f);
}

void set_near_z(st_camera *camera, float near)
{
    camera->near_z = near;
}

void set_far_z(st_camera *camera, float far)
{
    camera->far_z = far;
}

void set_ortho_size(st_camera *camera, float ortho_size)
{
    camera->ortho_size = ortho_size;
}

void set_rotation(st_camera *camera, float rotation)
{
    camera->rotation = rotation;
}

void set_pos(st_camera *camera, vec3 pos)
{
    // On paramètre la Position de la caméra
    glm_vec3_copy(pos , camera->pos);
}

void set_front(st_camera *camera, vec3 front)
{
    // On paramètre la Position de la caméra
    glm_vec3_copy(front , camera->front);
}

void set_up(st_camera *camera, vec3 up)
{
    // On paramètre la Position de la caméra
    glm_vec3_copy(up , camera->up);
    
}

float get_speed(st_camera *camera)
{
    return camera->speed;
}

void look(st_camera *camera)
{
    vec3 center;
    glm_vec3_sub(camera->pos, camera->front, center);
    glm_lookat(
        camera->pos, 
        center, 
        camera->up, 
        camera->view
    );
}

void camera_speed(st_camera *camera, float delta_time)
{
    camera->actual_speed = camera->speed * delta_time;
}

void update_ortho(st_camera *camera)
{
    glm_ortho(
        -camera->ortho_size * camera->ratio,
        camera->ortho_size * camera->ratio,
        -camera->ortho_size, camera->ortho_size, 
        camera->far_z, 
        camera->near_z, 
        camera->projection
    );
}