#include "../../../include/src_include/Context/View/view_main_menu_context.h"


void init_render(st_engine *engine_state){

    // Charger les shaders du context
    const char *vertex_shader_source = load_shader("src/Shaders/main_shader.vert");
    const char *fragment_shader_source = load_shader("src/Shaders/main_shader.frag");

    if(!vertex_shader_source || !fragment_shader_source)
    {
        printf("Attention, certains shaders n'ont pas élé chargé"
        "Le comportement du programme peux-être compromis.\n");
    }
    st_tile first_square;
    //st_tile seconde;

    load_file(BASIC_HOUSE_PATH, &first_square);
    //load_file(BASIC_HOUSE_PATH, &seconde);

    int i;
    for(i = 0; i < first_square.nb_vert; i ++)
    {
        printf("%f \n", first_square.vert_pos[i]);
    }
    
    for(i = 0; i < first_square.nb_face; i ++)
    {
        printf("%d \n", first_square.face_pos[i]);
    }
    printf("nb : %d\n", i);
/*
    for(i = 0; i < seconde.nb_vert; i ++)
    {
        printf("%f \n", seconde.vert_pos[i]);
    }
    for(i = 0; i < seconde.nb_face; i ++)
    {
        printf("%d \n", seconde.face_pos[i]);
    }
*/
    
    init_unsigned_int_lst(&engine_state->render.VAOs);
    init_unsigned_int_lst(&engine_state->render.VBOs);
    init_unsigned_int_lst(&engine_state->render.EBOs);

    init_unsigned_int_lst(&engine_state->render.shader_programs);

    init_a_3d_loaded_element(engine_state,  &first_square);
    //init_a_3d_loaded_element(engine_state,  &seconde);
    init_a_loaded_shader(engine_state, vertex_shader_source, fragment_shader_source);

    // Attention, si le dev va plus loin, il faudra sans doute garder
    // Ces position côté GPU aussi
    free(first_square.vert_pos);
    free(first_square.face_pos);

    // Libéré les shader qui sont compilé côté GPU à présent
    free((void *)vertex_shader_source);
    free((void *)fragment_shader_source);
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