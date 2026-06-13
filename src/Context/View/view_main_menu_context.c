#include "../../../include/src_include/Context/View/view_main_menu_context.h"


void init_render(st_engine *engine_state){
    const char *vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    const char *fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

    glClearColor(num_to_01(123), num_to_01(12), num_to_01(123), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };  

    // Tampon où l'on stock les sommets
    glGenVertexArrays(1, &engine_state->render_info.VAO);
    glGenBuffers(1, &engine_state->render_info.VBO);  
    printf("Bonjour\n");
    glBindVertexArray(engine_state->render_info.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, engine_state->render_info.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, engine_state->render_info.VBO);  

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    engine_state->render_info.vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(engine_state->render_info.vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(engine_state->render_info.vertex_shader);
    
    engine_state->render_info.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(engine_state->render_info.fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(engine_state->render_info.fragment_shader);

    engine_state->render_info.shader_program = glCreateProgram();
    
    // On lie le frag et le vert dans un seul prg
    glAttachShader(engine_state->render_info.shader_program, engine_state->render_info.vertex_shader);
    glAttachShader(engine_state->render_info.shader_program, engine_state->render_info.fragment_shader);
    glLinkProgram(engine_state->render_info.shader_program);
    
    // Une fois lié, l'on peux les supprimer
    glDeleteShader(engine_state->render_info.vertex_shader);
    glDeleteShader(engine_state->render_info.fragment_shader);

}
void update_render_main_menu(st_engine *engine_state){
    

    glUseProgram(engine_state->render_info.shader_program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glUseProgram(engine_state->render_info.shader_program);
    glBindVertexArray(engine_state->render_info.VBO);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    
}