#include "../../../include/src_include/Context/Model/model_game_context.h"


void update_logic_game(st_state *state)
{

    pthread_mutex_lock(&state->inputs.mutex); // Verrouillage
    // Géré les inputs
    if(state->inputs.release[KEY_DOWN] == true)
    {
        state->ev_next_context = C_BACK;   
        state->inputs.release[KEY_DOWN] = false;
    }
    if(state->inputs.release[KEY_ESCAPE] == true)
    {
        state->ev_must_close = true;  
        state->inputs.release[KEY_ESCAPE] = false; 
    }

    // Déplacement de la caméra
    if(state->inputs.release[KEY_Z] || state->inputs.pressed[KEY_Z])
    {
        state->inputs.release[KEY_Z] = false; 
        move_camera(&state->render.camera, UP);
    }
    if(state->inputs.release[KEY_Q] || state->inputs.pressed[KEY_Q])
    {
        state->inputs.release[KEY_Q] = false; 
        move_camera(&state->render.camera, LEFT);
    }
    if(state->inputs.release[KEY_S] || state->inputs.pressed[KEY_S])
    {
        state->inputs.release[KEY_S] = false; 
        move_camera(&state->render.camera, DOWN);
    }
    if(state->inputs.release[KEY_D] || state->inputs.pressed[KEY_D])
    {
        state->inputs.release[KEY_D] = false; 
        move_camera(&state->render.camera, RIGHT);
    }
    

    pthread_mutex_unlock(&state->inputs.mutex); // Déverrouillage

    /* On préviens l'autre thread que la lecture à bien été faite*/
    state->inputs.ok = true;
    
}

void init_data_game(st_state *state)
{
    // Initialiser les mutex
    pthread_mutex_init(&state->inputs.mutex, NULL);
}

void zoom_camera(st_camera *camera, float yoffset)
{
    if(camera->fov >= 1.0f && camera->fov <= 45.0f)
        camera->fov -= yoffset;
    if(camera->fov <= 1.0f)
        camera->fov = 1.0f;
    if(camera->fov >= 45.0f)
        camera->fov = 45.0f;
    }
void move_camera(st_camera *camera, int dir)
{
    vec3 res;

    switch (dir)
    {
    case UP:
        glm_vec3_muladds(camera->front, camera->speed, camera->pos);
        break;

    case LEFT:

        glm_cross(camera->front, camera->up, res);

        glm_vec3_normalize(res);
        glm_vec3_mulsubs(res, camera->speed, camera->pos);

        break;

    case DOWN:
        glm_vec3_mulsubs(camera->front, camera->speed, camera->pos);

        break;
    case RIGHT:
        
        glm_cross(camera->front, camera->up, res);

        glm_vec3_normalize(res);
        glm_vec3_muladds(res, camera->speed, camera->pos);

        break;
    
    default:
        break;
    }
    
}

