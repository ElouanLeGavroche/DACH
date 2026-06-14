#include "../../../include/src_include/Context/View/view_main_menu_context.h"


void init_render(st_engine *engine_state){

    // Charger les shaders du context
    const char *vertex_shader_source = load_shader("src/Shaders/main_shader.vert");
    const char *fragment_shader_source = load_shader("src/Shaders/main_shader.frag");
    const char *fragment_shader_source_2 = load_shader("src/Shaders/main_menu_shader.frag");

    st_tile first_square;

    load_file(BASIC_TILE_PATH, &first_square);


    engine_state->render_info.VAOs.elt = EMPTY_LIST;
    engine_state->render_info.VBOs.elt = EMPTY_LIST;
    engine_state->render_info.EBOs.elt = EMPTY_LIST;

    engine_state->render_info.shader_programs.elt = EMPTY_LIST;


    init_a_3d_loaded_element(engine_state,  &first_square);
    init_a_loaded_shader(engine_state, vertex_shader_source, fragment_shader_source);

    
}
void update_render_main_menu(st_engine *engine_state){
    
    glClearColor(num_to_01(123), num_to_01(12), num_to_01(123), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(get_by_indice(&engine_state->render_info.shader_programs, 0).elt);

    glBindVertexArray(get_by_indice(&engine_state->render_info.VAOs, 0).elt);
    
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    
    
}

void change_render_mode(st_engine *engine_state)
{
    if(engine_state->render_info.render_mode != GL_FILL)
    {
        engine_state->render_info.render_mode = GL_FILL;
    } 
    else
    {
        engine_state->render_info.render_mode = GL_LINE;
    }
    
    glPolygonMode(GL_FRONT_AND_BACK, engine_state->render_info.render_mode);
}