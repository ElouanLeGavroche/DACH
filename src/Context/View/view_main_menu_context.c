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