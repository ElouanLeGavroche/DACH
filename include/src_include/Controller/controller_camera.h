#ifndef CONTROLLER_CAMERA
#define CONTROLLER_CAMERA

#include "../Config/constantes.h"
#include "../../types.h"

#include "../Model/model_camera.h"

void controller_init_camera(st_camera *camera, float speed, float near, float far, float size, float rotation);
void controller_init_camera_vector(st_camera *camera, vec3 pos, vec3 front, vec3 up);
void controller_init_camera_view(st_camera *camera);

#endif