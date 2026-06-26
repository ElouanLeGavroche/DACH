#include "../../../include/src_include/Context/Model/model_game_context.h"


void update_logic_game(st_engine *engine_state)
{

    pthread_mutex_lock(&engine_state->stack_context.current_state->inputs.mutex); // Verrouillage
    // Géré les inputs
    if(engine_state->stack_context.current_state->inputs.release[KEY_DOWN] == true)
    {
        engine_state->stack_context.current_state->ev_next_context = C_BACK;   
    }
    if(engine_state->stack_context.current_state->inputs.release[KEY_ESCAPE] == true)
    {
        engine_state->stack_context.current_state->ev_must_close = true;   
    }

    // Déplacement de la caméra
    if(engine_state->stack_context.current_state->inputs.release[KEY_Z] || engine_state->stack_context.current_state->inputs.pressed[KEY_Z])
    {
        move_camera(&engine_state->stack_context.current_state->render.camera, UP);
    }
    if(engine_state->stack_context.current_state->inputs.release[KEY_Q] || engine_state->stack_context.current_state->inputs.pressed[KEY_Q])
    {
        move_camera(&engine_state->stack_context.current_state->render.camera, LEFT);
    }
    if(engine_state->stack_context.current_state->inputs.release[KEY_S] || engine_state->stack_context.current_state->inputs.pressed[KEY_S])
    {
        move_camera(&engine_state->stack_context.current_state->render.camera, DOWN);
    }
    if(engine_state->stack_context.current_state->inputs.release[KEY_D] || engine_state->stack_context.current_state->inputs.pressed[KEY_D])
    {
        move_camera(&engine_state->stack_context.current_state->render.camera, RIGHT);
    }

    pthread_mutex_unlock(&engine_state->stack_context.current_state->inputs.mutex); // Déverrouillage

    /* On préviens l'autre thread que la lecture à bien été faite*/
    engine_state->stack_context.current_state->inputs.ok = true;
    
}

void init_data_game(st_state *state)
{
    // Initialiser les mutex
    pthread_mutex_init(&state->inputs.mutex, NULL);
}

void move_camera(st_camera *camera, int dir)
{
    if(dir == UP)
        glm_vec3_addadd((vec3){0.05f}, camera->camera_front, camera->camera_pos);
    
    else if(dir == LEFT)
        glm_vec3_addadd((vec3){0.05f}, camera->camera_front, camera->camera_pos);
    
    else if(dir == DOWN)
        glm_vec3_addadd((vec3){0.05f}, camera->camera_front, camera->camera_pos);
    
    else if(dir == RIGHT)
        glm_vec3_addadd((vec3){0.05f}, camera->camera_front, camera->camera_pos);
    
}

