#include "../../../include/src_include/Context/View/view_game_context.h"

void update_render_game(st_render_data *render){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Model */
    mat4 model;
    glm_mat4_identity(model);
    glm_rotate(model, (float)glfwGetTime()*10, (vec3){0.0f, 0.0f, 1.0f});

    /* View */
    /*
    mat4 view;
    glm_mat4_identity(view);
    glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});
    */

    /* Projection en perspective */
    mat4 proj;
    glm_mat4_identity(proj);
    glm_perspective(glm_rad(45.0f), (float)1280/(float)720, 0.1f, 100.0f, proj);

    /* Ici l'on actualise = tout les éléments du menu */
    mat4 trans;
    glm_mat4_identity(trans);

    glm_rotate(trans, (float)glfwGetTime(), (vec3){1.0, 1.0, 1.0});
    glm_scale(trans, (vec3){0.5, 0.5, 0.5});

    float radius = 10.0f;
    float cam_x = sin(glfwGetTime()) * radius;
    float cam_z = cos(glfwGetTime()) * radius;

    mat4 view;
    glm_mat4_identity(view);

    glm_lookat((vec3){cam_x, 0.0, cam_z}, (vec3){0.0, 0.0, 0.0}, (vec3){0.0, 1.0, 0.0}, view);

    unsigned int transfrom_loc;
    
    //glm_translate(trans, (vec3){1.0f, 1.0f, 0.0f});
    //vec4 result;
    
    //glm_mat4_mulv(trans, vec, result);
    //printf("%f %f %f\n", result[0], result[1], result[2]);


        float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_pos += cameraSpeed * camera_front;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_pos -= cameraSpeed * camera_front;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)

        camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
    
    
    glClearColor(num_to_01(24), num_to_01(32), num_to_01(61), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(render->shader_programs[0].shader);
    
    int model_loc = glGetUniformLocation(render->shader_programs[0].shader, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, *model);

    int view_loc = glGetUniformLocation(render->shader_programs[0].shader, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, *view);
    
    int proj_loc = glGetUniformLocation(render->shader_programs[0].shader, "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, *proj);


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