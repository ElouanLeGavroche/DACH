#include "../../../include/src_include/Context/View/view_game_context.h"


void init_render_game(st_render_data *render)
{

    render->delta_time = 0.0f;
    render->last_time = 0.0f;

    render->camera.fov = 45.0f;
    render->camera.speed = 0.0f;
    
    glm_mat4_identity(render->camera.view);

    /* Projection en perspective */
    /*
    glm_mat4_identity(render->camera.projection);
    glm_perspective(glm_rad(render->camera.fov), (float)1280/(float)720, 0.1f, 100.0f, render->camera.projection);
    */

    float size = 10.0f; // Taille de la zone visible (à ajuster selon ta scène)
    glm_ortho(-size, size, -size, size, -100.0f, 100.0f, render->camera.projection);


    // On initialise la position de la caméra à une vue isométrique
    glm_vec3_copy((vec3){2.0f, 2.0f, 2.0f} , render->camera.pos);
    glm_vec3_copy((vec3){0.45, 0.45, 0.45} , render->camera.front);
    glm_vec3_copy((vec3){0.0, 1.0, 0.0} , render->camera.up);

    vec3 center;

    glm_vec3_sub(render->camera.pos, render->camera.front, center);
    glm_lookat(render->camera.pos, center, render->camera.up, render->camera.view);


    // On va associé la caméra dans Opengl, car on peut-en avoir besoin dans les callbacks
    GLFWwindow *window = glfwGetCurrentContext();

    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->camera = &render->camera;
}

void update_render_game(st_render_data *render)
{
    float current_frame = glfwGetTime();
    render->delta_time = current_frame - render->last_time;
    render->last_time = current_frame;

    render->camera.speed = 2.5f *render->delta_time;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Ici l'on actualise = tout les éléments du menu */
    mat4 trans;
    glm_mat4_identity(trans);


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

    glClearColor(num_to_01(24), num_to_01(32), num_to_01(61), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(render->shader_programs[0].shader);
    
    int model_loc = glGetUniformLocation(render->shader_programs[0].shader, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, *model);

    int view_loc = glGetUniformLocation(render->shader_programs[0].shader, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, *render->camera.view);
    
    int proj_loc = glGetUniformLocation(render->shader_programs[0].shader, "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, *render->camera.projection);


    transfrom_loc = glGetUniformLocation(render->shader_programs[0].shader, "transform");
    glUniformMatrix4fv(transfrom_loc, 1, GL_FALSE, *trans);
    
    int i;
    for(i = 0; i < render->nb_mesh; i ++)
    {

        glBindVertexArray(render->meshs[i].VAO);
        glDrawElements(GL_TRIANGLES, render->meshs[i].nb_face, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}