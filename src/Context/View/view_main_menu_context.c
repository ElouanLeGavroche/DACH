#include "../../../include/src_include/Context/View/view_main_menu_context.h"

void init_mesh(st_engine *engine_state, st_mesh mesh)
{
    init_a_3d_loaded_element(engine_state,  &mesh);
    // Vider côté CPU
    free(mesh.vert_pos);
    free(mesh.face_pos);
}

void update_render_main_menu(st_engine *engine_state){
    
    glClearColor(num_to_01(123), num_to_01(12), num_to_01(123), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(get_unsigned_int_lst_pointer(engine_state->render.shader_programs, 0)->value);

    glBindVertexArray(get_unsigned_int_lst_pointer(engine_state->render.VAOs, 0)->value);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
    /*
    glBindVertexArray(get_unsigned_int_lst_pointer(&engine_state->render.VAOs, 1).elt);
    glDrawElements(GL_TRIANGLES, sizeof(get_unsigned_int_lst_pointer(&engine_state->render.VAOs, 1)), GL_UNSIGNED_INT, 0);
    */
    glBindVertexArray(0);
    
    
}

void change_render_mode(st_engine *engine_state)
{
    if(engine_state->render.render_mode != GL_FILL)
    {
        engine_state->render.render_mode = GL_FILL;
    } 
    else
    {
        engine_state->render.render_mode = GL_LINE;
    }
    
    glPolygonMode(GL_FRONT_AND_BACK, engine_state->render.render_mode);
}