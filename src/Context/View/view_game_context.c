#include "../../../include/src_include/Context/View/view_game_context.h"


void init_render_game(st_render_data *render)
{

    render->nb_groups = 0;
    render->nb_total_groups = 0;
    
    init_game_camera(&render->camera);


    // On va associé la caméra dans Opengl, car on peut-en avoir besoin dans les callbacks
    GLFWwindow *window = glfwGetCurrentContext();

    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->camera = &render->camera; 
}

void create_an_instance_GPU(st_instanced *instance, mat4 *model, int amount)
{
    int i;
    unsigned int instance_vbo;
    glGenBuffers(1, &instance_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(mat4), &model[0], GL_STATIC_DRAW);

    // On va diviser le model en 4 partie pour l'envoier au GPU
    // via les in layout, et c'est lui qui s'occupera de les reformer

    for(i = 0; i < 4; i ++)
    {
        
        glEnableVertexAttribArray(3 + i);
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*) (i* sizeof(vec4)) );
        glVertexAttribDivisor(3 + i, 1);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    instance->vbo = instance_vbo;
}

void init_game_camera(st_camera *camera)
{
    // Vitesse absolue de la caméra
    camera->speed = 30.0f;
    // Vitesse relative de la caméra
    camera->actual_speed = 0.0f;
    // ortho_size de la fenêtre
    camera->ratio = ((float)SCREEN_WITH_DEFAULT / (float)SCREEN_HEIGHT_DEFAULT) * (4.0f / 3.0f);
    // Rendu le plus proche
    camera->near_z = -1000.0f;
    // Rendu le plus loin
    camera->far_z = 1000.0f; 
    // Taille du champ de vision (N 15; S 15, E 15, W 15)
    camera->ortho_size = 250.0f;
    // Valeur de l'angle de rotatio
    camera->rotation = 45.0f;

    vec3 center;

    // Création de la vue Orthogonale avec les paramètres déclarer plus haut
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

    /* On initialise la position de la caméra à une vue isométrique */
    
    // On paramètre la Position de la caméra
    glm_vec3_copy((vec3){2.0f, 2.0f, 2.0f} , camera->pos);
    // Vecteur qui correspond à ce que regarde la caméra
    glm_vec3_copy((vec3){0.450, 0.250, 0.450} , camera->front);
    // Vecteur haut
    glm_vec3_copy((vec3){0.0, 1.0, 0.0} , camera->up);

    /* Définition du LookAt*/
    //glm_vec3_sub(camera->pos, camera->front, center);
    glm_lookat(camera->pos, camera->front, camera->up, camera->view);

}

void update_render_game(st_render_data *render)
{


    view_render(render);
}