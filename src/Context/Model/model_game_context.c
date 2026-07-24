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
    if(state->inputs.release[KEY_A])
    {
        move_camera(&state->render.camera, ROTATE_L);
        state->inputs.release[KEY_A] = false;
    }
    if(state->inputs.release[KEY_E])
    {
        move_camera(&state->render.camera, ROTATE_R);
        state->inputs.release[KEY_E] = false;
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
        // à l'avenir, il faudra crée un fichier pour regrouper les système d'animations
        pthread_t rotate_l;
        camera->rotation = -45.0f;
        pthread_create(&rotate_l, NULL, rotate_animation, camera);

        break;
    
    case ROTATE_R:
        pthread_t rotate_r;
        camera->rotation = 45.0f;
        pthread_create(&rotate_r, NULL, rotate_animation, camera);
        break;

    default:
        break;
    }
    
}

// Fonction temporaire, ce n'est pas propre, juste temporaire
void *rotate_animation(void *camera_data){
    st_camera *camera = camera_data;
    int i;
    struct timespec ts_start, ts_end;
    double elapsed;
    float rotate_value = abs(camera->rotation) / camera->rotation;

    for(i = 0; i < 45; i ++)
    {
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        rotate(camera, rotate_value);

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_frame(ts_start, ts_end);
    }

}

mat4* init_map(int amount, st_loaded_tile_map *tiles)
{   
    int i, y;
    mat4 *positions = malloc(sizeof(mat4) * (amount));
    
    if(!positions)
    {
        fprintf(stderr, "Allocation échouer : %s\n", strerror(errno));
        return NULL;
    }
    
    /*
    int total = 0;
    for(i = amount; i > 0; i --)
    {
        for(y = amount; y > 0; y --)
        {
            
            glm_mat4_identity(positions[total]);
            glm_translate(positions[total], (vec3){(float)i * 2.0f - amount, 0.0, (float)y * 2.0f - amount});
            total ++;
        }
    }
    */
    int total = 0;
    for(i = 0; i < amount; i ++)
    {
        glm_mat4_identity(positions[total]);
        glm_translate(positions[total], (vec3){(float)tiles[i].x_indice * 2.0f, (float)tiles[i].height_value, (float)tiles[i].y_indice * 2.0f });
        total ++;
    }

    return positions;
}