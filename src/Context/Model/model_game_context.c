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
    if(state->inputs.down[KEY_Z] || state->inputs.pressed[KEY_Z])
    {
        move_camera(&state->render.camera, UP);
    }
    if(state->inputs.down[KEY_Q] || state->inputs.pressed[KEY_Q])
    {
        move_camera(&state->render.camera, LEFT);
    }
    if(state->inputs.down[KEY_S] || state->inputs.pressed[KEY_S])
    {
        move_camera(&state->render.camera, DOWN);
    }
    if(state->inputs.down[KEY_D] || state->inputs.pressed[KEY_D])
    {
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

void move_camera(st_camera *camera, int dir)
{
    vec3 res;

    switch (dir)
    {
    case DOWN:
        glm_vec3_mulsubs(camera->up, camera->actual_speed * 3, camera->pos);
        break;

    case RIGHT:

        glm_cross(camera->front, camera->up, res);

        glm_vec3_normalize(res);
        glm_vec3_mulsubs(res, camera->actual_speed, camera->pos);

        break;

    case UP:
        glm_vec3_muladds(camera->up, camera->actual_speed * 3, camera->pos);
        break;
    case LEFT:
        
        glm_cross(camera->front, camera->up, res);

        glm_vec3_normalize(res);
        glm_vec3_muladds(res, camera->actual_speed, camera->pos);

        break;
    
    default:
        break;
    }
    
}

mat4* init_map(int amount)
{   
    int i, y;
    mat4 *positions = malloc(sizeof(mat4) * (amount));
    
    if(!positions)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return NULL;
    }
    

    int size_map = 52;
    int total = 0;
    for(i = size_map; i > 0; i --)
    {
        for(y = size_map - 1; y > 0; y --)
        {
            
            glm_mat4_identity(positions[total]);
            glm_translate(positions[total], (vec3){(float)i * 2.0f - size_map, 0.0, (float)y * 2.0f - size_map});
            total ++;
        }
    }

    return positions;
}