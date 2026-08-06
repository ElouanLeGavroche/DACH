#include "../../../include/src_include/Context/Model/model_game_context.h"

void update_logic_game(st_context *state)
{

    // Géré les inputs
    if(state->inputs.release[KEY_DOWN] == true)
    {
        state->request.target = C_BACK;
        state->request.action = CONTEXT_ACTION_POP;

        state->inputs.release[KEY_DOWN] = false;
    }
    if(state->inputs.release[KEY_ESCAPE] == true)
    {
        state->request.action = CONTEXT_ACTION_QUIT;
        state->request.target = C_GAME;
        
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
    if(state->inputs.release[KEY_A])
    {
        //move_camera(&state->render.camera, ROTATE_L);
        state->render.camera.target = (state->render.camera.target <= 0.0f)? 45.0f + state->render.camera.target: state->render.camera.target;
        state->inputs.release[KEY_A] = false;
    }
    if(state->inputs.release[KEY_E])
    {
        //move_camera(&state->render.camera, ROTATE_R);
        state->render.camera.target = (state->render.camera.target >= -0.0f)? -45.0f + state->render.camera.target: state->render.camera.target;
        state->inputs.release[KEY_E] = false;
    }
    if(state->render.camera.target != 0.0f)
    {
        move_camera(&state->render.camera, (state->render.camera.target > 0.0f) ? ROTATE_L : ROTATE_R);
    }
    
}


void move_camera(st_camera *camera, int dir, st_mouse *mouse)
{
    switch (dir)
    {
    case DOWN:
        down(camera);
        break;

    case RIGHT:
        right(camera);
        break;

    case UP:
        up(camera);
        break;

    case LEFT:
        left(camera);
        break;

    case ROTATE_L:
        camera->target --;
        rotate(camera, -1.0f);

        break;
    
    case ROTATE_R:
        camera->target ++;
        rotate(camera, 1.0f);
        break;

    default:
        break;
    }

    // Gestion du zoom
    if(camera->ortho_size >= 3.0f && camera->ortho_size <= 25.0f)
        camera->ortho_size -= yoffset;
    if(camera->ortho_size <= 3.0f)
        camera->ortho_size = 3.0f;
    if(camera->ortho_size >= 25.0f)
        camera->ortho_size = 25.0f;
    
}

mat4* init_map(int amount, st_loaded_tile_map *tiles)
{   
    int i;
    mat4 *positions = malloc(sizeof(mat4) * (amount));
    
    if(!positions)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return NULL;
    }
    
    int total = 0;
    for(i = 0; i < amount; i ++)
    {
        glm_mat4_identity(positions[total]);
        glm_translate(positions[total], (vec3){(float)tiles[i].x_indice * 2.0f, (float)tiles[i].height_value, (float)tiles[i].y_indice * 2.0f });
        total ++;
    }

    return positions;
}