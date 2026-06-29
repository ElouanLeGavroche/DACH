#include "../../../include/src_include/Context/View/view_game_context.h"


void init_render_game(st_render_data *render)
{

    init_game_camera(&render->camera);


    // On va associé la caméra dans Opengl, car on peut-en avoir besoin dans les callbacks
    GLFWwindow *window = glfwGetCurrentContext();

    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->camera = &render->camera;
}

void init_game_camera(st_camera *camera)
{
    // Vitesse absolue de la caméra
    camera->speed = 4.0f;
    // Vitesse relative de la caméra
    camera->actual_speed = 0.0f;
    // Taille du champ de vision (N 15; S 15, E 15, W 15)
    camera->fov = 15.0f;
    // Rendu le plus proche
    camera->near_z = -100.0f;
    // Rendu le plus loin
    camera->far_z = 100.0f; 

    vec3 center;

    // initialisation du point de vue
    glm_mat4_identity(camera->view);

    // Création de la vue Orthogonale avec les paramètres déclarer plus haut
    glm_ortho(
        //Champ de vue
        -camera->fov, camera->fov, -camera->fov, camera->fov, 
        // Profondeur de champ
        camera->near_z, camera->far_z, 
        // Matrice de projection
        camera->projection
    );

    /* On initialise la position de la caméra à une vue isométrique */
    
    // On paramètre la Position de la caméra
    glm_vec3_copy((vec3){2.0f, 2.0f, 2.0f} , camera->pos);
    // Vecteur qui correspond à ce que regarde la caméra
    glm_vec3_copy((vec3){0.125, 0.125, 0.125} , camera->front);
    // Vecteur haut
    glm_vec3_copy((vec3){0.0, 0.25, 0.0} , camera->up);

    /* Définition du LookAt*/
    glm_vec3_sub(camera->pos, camera->front, center);
    glm_lookat(camera->pos, center, camera->up, camera->view);

}

void update_render_game(st_render_data *render)
{
    /* 
    On va en premier lieu calculer le temps que prend une frame à être fait
    ainsi, la caméra ne dépendant plus de la vitesse du jeu .
    */

    float current_frame = glfwGetTime();
    render->delta_time = current_frame - render->last_time;
    render->last_time = current_frame;

    render->camera.actual_speed = render->camera.speed *render->delta_time;

        /* Model */
    mat4 model;
    glm_mat4_identity(model);
    //glm_rotate(model, (float)glfwGetTime()*2, (vec3){0.0f, 0.0f, 1.0f});
  
    unsigned int transfrom_loc;
    
    vec3 center;

    glm_vec3_sub(render->camera.pos, render->camera.front, center);
    glm_lookat(
        render->camera.pos, 
        center, 
        render->camera.up, 
        render->camera.view
    );

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(num_to_01(24), num_to_01(32), num_to_01(61), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(render->shader_programs[0].shader);
    
    /* Application de la rotation */
    int model_loc = glGetUniformLocation(render->shader_programs[0].shader, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, *model);

    /* Application du point de vue */
    int view_loc = glGetUniformLocation(render->shader_programs[0].shader, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, *render->camera.view);
    
    /* Application de la projection*/
    int proj_loc = glGetUniformLocation(render->shader_programs[0].shader, "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, *render->camera.projection);

    
    int i;
    for(i = 0; i < render->nb_mesh; i ++)
    {
        // Pour les texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, render->meshs[i].texture_id);
        
        glBindVertexArray(render->meshs[i].VAO);
        glDrawElements(GL_TRIANGLES, render->meshs[i].nb_face, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}