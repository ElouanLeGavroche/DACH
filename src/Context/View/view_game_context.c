#include "../../../include/src_include/Context/View/view_game_context.h"


void init_render_game(st_render_data *render)
{

    glm_mat4_identity(render->camera.view);

    /* Projection en perspective */
    glm_mat4_identity(render->camera.projection);
    glm_perspective(glm_rad(45.0f), (float)1280/(float)720, 0.1f, 100.0f, render->camera.projection);

    // On initialise la position de la caméra
    glm_vec3_copy((vec3){1.0f, 0.0f, 1.0f} , render->camera.camera_pos);
    glm_vec3_copy((vec3){0.0, 0.0, -1.0} , render->camera.camera_front);

    vec3 center;

    glm_vec3_sub(render->camera.camera_pos, render->camera.camera_front, center);
    glm_lookat((vec3){1.0, 0.0, 1.0}, center,(vec3){0.0, 1.0, 0.0}, render->camera.view);

    //glm_translate(trans, (vec3){1.0f, 1.0f, 0.0f});
    //vec4 result;
    
    //glm_mat4_mulv(trans, vec, result);
    //printf("%f %f %f\n", result[0], result[1], result[2]);

}
void update_render_game(st_render_data *render)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Ici l'on actualise = tout les éléments du menu */
    mat4 trans;
    glm_mat4_identity(trans);


        /* Model */
    mat4 model;
    glm_mat4_identity(model);
    glm_rotate(model, (float)glfwGetTime()*10, (vec3){0.0f, 0.0f, 1.0f});
  
    unsigned int transfrom_loc;
    
    vec3 center;

    glm_vec3_sub(render->camera.camera_pos, render->camera.camera_front, center);
    glm_lookat(render->camera.camera_pos, center, (vec3){0.0, 1.0, 0.0}, render->camera.view);

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