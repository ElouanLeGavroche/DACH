#include "../../../include/src_include/Context/Model/model_pause_menu_context.h"

void update_logic_pause_menu(st_context *state)
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
        state->request.action = CONTEXT_ACTION_POP;
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

    zoom_camera(&state->render.camera, &state->mouse);    
}
