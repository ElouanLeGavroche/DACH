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

void init_world(st_instanced *instance, mat4 *model, int amount)
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
    camera->speed = 4.0f;
    // Vitesse relative de la caméra
    camera->actual_speed = 0.0f;
    // ortho_size de la fenêtre
    camera->ratio = ((float)SCREEN_WITH_DEFAULT / (float)SCREEN_HEIGHT_DEFAULT) * (4.0f / 3.0f);
    // Rendu le plus proche
    camera->near_z = -100.0f;
    // Rendu le plus loin
    camera->far_z = 100.0f; 
    // Taille du champ de vision (N 15; S 15, E 15, W 15)
    camera->ortho_size = 15.0f;

    vec3 center;

    // initialisation du point de vue
    glm_mat4_identity(camera->view);

    // Création de la vue Orthogonale avec les paramètres déclarer plus haut
    glm_ortho(
        //Champ de vue
        -camera->ortho_size - camera->ratio, 
        camera->ortho_size + camera->ratio, 
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
    glm_vec3_copy((vec3){0.125, 0.125, 0.125} , camera->front);
    // Vecteur haut
    glm_vec3_copy((vec3){0.0, 0.25, 0.0} , camera->up);

    /* Définition du LookAt*/
    glm_vec3_sub(camera->pos, camera->front, center);
    glm_lookat(camera->pos, center, camera->up, camera->view);

}

void update_render_game(st_render_data *render)
{
    int i, y;
    /* 
    On va en premier lieu calculer le temps que prend une frame à être fait
    ainsi, la caméra ne dépendant plus de la vitesse du jeu .
    */
    glDepthFunc(GL_LESS);  
    float current_frame = glfwGetTime();
    render->delta_time = current_frame - render->last_time;
    render->last_time = current_frame;

    render->camera.actual_speed = render->camera.speed *render->delta_time;

    /* Model */
    mat4 model;
    glm_mat4_identity(model);
    glm_rotate(model, (float)glfwGetTime()*2, (vec3){0.0f, 0.0f, 1.0f});
    glm_translate(model, (vec3){0.0f, 0.0f, (float)glfwGetTime()*2});
    unsigned int transfrom_loc;
    
    vec3 center;

    glm_vec3_sub(render->camera.pos, render->camera.front, center);
    glm_lookat(
        render->camera.pos, 
        center, 
        render->camera.up, 
        render->camera.view
    );
    

    glClearColor(num_to_01(24), num_to_01(32), num_to_01(61), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    st_instanced_mesh_group *group = (st_instanced_mesh_group*)render->groups[0].data;
    st_render_object *obj = group->shared_render_object;
    glUseProgram(obj->material->shader.shader);

    /* Application du point de vue */
    int view_loc = glGetUniformLocation(obj->material->shader.shader, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, &render->camera.view[0][0]);
    
    /* Application de la projection*/
    int proj_loc = glGetUniformLocation(obj->material->shader.shader, "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &render->camera.projection[0][0]);

    // Lié le VAO
    glBindVertexArray(obj->mesh->VAO);
    
    glDrawElementsInstanced(GL_TRIANGLES, obj->mesh->index_count, GL_UNSIGNED_INT, 0, group->st_instanced.count);
    //glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
    glBindVertexArray(0);

}