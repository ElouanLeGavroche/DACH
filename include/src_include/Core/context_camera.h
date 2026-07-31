#ifndef CONTEXT_CAMERA
#define CONTEXT_CAMERA

#include "../Config/constantes.h"
#include "../../types.h"

#include "../Model/model_camera.h"

void init_camera(st_camera *camera, float speed, float near, float far, float size, float rotation);
void init_camera_vector(st_camera *camera, vec3 pos, vec3 front, vec3 up);
void init_camera_view(st_camera *camera);

#include "../../types.h"
#include "../Config/constantes.h"

void model_init_camera_view(st_camera *camera);

void up(st_camera *camera);
void down(st_camera *camera);
void left(st_camera *camera);
void right(st_camera *camera);

void rotate(st_camera *camera, float deg);

/* Getters et Setters */
void set_speed(st_camera *camera, float speed);
void set_actual_speed(st_camera *camera, float speed);
void set_ratio(st_camera *camera);
void set_near_z(st_camera *camera, float near);
void set_far_z(st_camera *camera, float far);
void set_ortho_size(st_camera *camera, float ortho_size);
void set_rotation(st_camera *camera, float rotation);
void set_pos(st_camera *camera, vec3 pos);
void set_front(st_camera *camera, vec3 front);
void set_up(st_camera *camera, vec3 up);

/* Méthode publique (accessible en dehors de controller, model de camera)*/
void look(st_camera *camera);
void camera_speed(st_camera *camera, float delta_time);

#endif