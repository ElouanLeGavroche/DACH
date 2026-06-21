#include "../../../include/src_include/Context/View/view_main_menu_context.h"
void init_mesh(st_render_data *render, st_mesh mesh)
{
    init_a_3d_loaded_element(render,  &mesh);
    // Vider côté CPU
    free(mesh.vert_pos);
    free(mesh.face_pos);
}

void update_render_main_menu(st_render_data *render)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Model */
    mat4 model;
    glm_mat4_identity(model);
    glm_rotate(model, glm_rad(-55.0f), (vec3){1.0f, 0.0f, 0.0f});

    /* View */
    mat4 view;
    glm_mat4_identity(view);
    glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});

    /* Projection en perspective */
    mat4 proj;
    glm_mat4_identity(proj);
    glm_perspective(glm_rad(45.0f), (float)1280/(float)720, 0.1f, 100.0f, proj);

    /* Ici l'on actualise = tout les éléments du menu */
    mat4 trans;
    glm_mat4_identity(trans);

    glm_rotate(trans, (float)glfwGetTime(), (vec3){1.0, 1.0, 1.0});
    glm_scale(trans, (vec3){0.5, 0.5, 0.5});

    unsigned int transfrom_loc;

    //glm_translate(trans, (vec3){1.0f, 1.0f, 0.0f});
    //vec4 result;
    
    //glm_mat4_mulv(trans, vec, result);
    //printf("%f %f %f\n", result[0], result[1], result[2]);


    glClearColor(num_to_01(0), num_to_01(0), num_to_01(0), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(get_unsigned_int_lst_pointer(render->shader_programs, 0)->value);

    int model_loc = glGetUniformLocation(get_unsigned_int_lst_pointer(render->shader_programs, 0)->value, "model");
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, *model);

    int view_loc = glGetUniformLocation(get_unsigned_int_lst_pointer(render->shader_programs, 0)->value, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, *view);

    int proj_loc = glGetUniformLocation(get_unsigned_int_lst_pointer(render->shader_programs, 0)->value, "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, *proj);


    transfrom_loc = glGetUniformLocation(get_unsigned_int_lst_pointer(render->shader_programs, 0)->value, "transform");
    glUniformMatrix4fv(transfrom_loc, 1, GL_FALSE, *trans);

    int i;
    int nb_elt = render->VAOs->size;
    for(i = 0; i < nb_elt; i ++)
    {

        glBindVertexArray(get_unsigned_int_lst_pointer(render->VAOs, i)->value);
        glDrawElements(GL_TRIANGLES, render->VAOs->first->nb_face, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }
    
}

void change_render_mode(st_render_data *render)
{
    /* Passage d'un rendu plein à un rendu filaire (pour le debug) */
    if(render->render_mode != GL_FILL)
    {
        render->render_mode = GL_FILL;
    } 
    else
    {
        render->render_mode = GL_LINE;
    }
    
    glPolygonMode(GL_FRONT_AND_BACK, render->render_mode);
}