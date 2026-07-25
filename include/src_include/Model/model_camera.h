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