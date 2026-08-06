#include "../../../include/src_include/Context/View/view_game_context.h"


void init_render_game(st_render_data *render)
{

    render->nb_groups = 0;
    render->nb_total_groups = 0;
    
    //init_game_camera(&render->camera);


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

void update_render_game(st_render_data *render)
{
    int i;
    /* 
    On va en premier lieu calculer le temps que prend une frame à être fait
    ainsi, la caméra ne dépendant plus de la vitesse du jeu .
    */
    glDepthFunc(GL_LESS);  
    float current_frame = glfwGetTime();
    render->delta_time = current_frame - render->last_time;
    render->last_time = current_frame;

    render->camera.camera_speed(&render->camera, render->delta_time);

    /* Model */
    mat4 model;
    glm_mat4_identity(model);
    //glm_rotate(model, (float)glfwGetTime()*2, (vec3){0.5f, 0.5f, 1.0f});
    glm_translate(model, (vec3){0.0f, 0.0f, sin((float)glfwGetTime()*2)});
    
    render->camera.look(&render->camera);
    
    glClearColor(num_to_01(24), num_to_01(32), num_to_01(61), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(i = 0; i < render->nb_groups; i ++)
    {
        st_instanced_mesh_group *group = (st_instanced_mesh_group*)render->groups[i].data;
        st_render_object *obj = group->shared_render_object;

        glUseProgram(obj->material->shader->shader);
        glBindTexture(GL_TEXTURE_2D, obj->material->texture->id);

        /* Application du point de vue */
        int view_loc = glGetUniformLocation(obj->material->shader->shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, &render->camera.view[0][0]);
        
        /* Application de la projection*/
        int proj_loc = glGetUniformLocation(obj->material->shader->shader, "projection");
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &render->camera.projection[0][0]);

        /* application d'une transformation bidon */
        unsigned int transfrom_loc = glGetUniformLocation(obj->material->shader->shader, "transform");;
        glUniformMatrix4fv(transfrom_loc, 1, GL_FALSE, *model);

        // Lié le VAO
        glBindVertexArray(obj->mesh->VAO);
        
        glDrawElementsInstanced(GL_TRIANGLES, obj->mesh->index_count, GL_UNSIGNED_INT, 0, group->st_instanced.count);
        glBindVertexArray(0);
    }

}