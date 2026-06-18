#include "../../../include/src_include/Context/View/view_main_menu_context.h"

void init_mesh(st_render_data *render, st_mesh mesh)
{
    init_a_3d_loaded_element(render,  &mesh);
    // Vider côté CPU
    free(mesh.vert_pos);
    free(mesh.face_pos);
}

void update_render_main_menu(st_render_data *render){
    /* Ici l'on actualise = tout les éléments du menu */
    
    glClearColor(num_to_01(0), num_to_01(0), num_to_01(0), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(get_unsigned_int_lst_pointer(render->shader_programs, 0)->value);
    
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