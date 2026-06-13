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


    float first_square[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,   // top left

        -0.7f,  0.5f, 0.0f, 
        -0.5f, 0.5f, 0.0f,  
        -0.7f, 0.0f, 0.0f, 
        -0.5f,  0.0f, 0.0f   
    };
    
    unsigned int indices[] = {
    0, 1, 3,   // premier triangle
    1, 2, 3,    // second triangle

    4,5,6,
    5,7,6
    };
    
    engine_state->render_info.VAOs.elt = -1;
    engine_state->render_info.VBOs.elt = -1;
    engine_state->render_info.EBOs.elt = -1;

    
    
    

    int i;
    for(i = 0; i < 2; i ++)
    {
        unsigned int VAO, VBO, EBO;

        
        // Tampon où l'on stock les sommets
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);  
        glGenBuffers(1, &EBO);

        // 1.Attacher le VAO (Vertex Array Object)
        glBindVertexArray(VAO);

        // 2.Mettre les sommet dans le VBO et EBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(first_square), first_square, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        printf("%d Bonjour\n", EBO);
        add_to_unsigned_list(&engine_state->render_info.VAOs, VAO);
        add_to_unsigned_list(&engine_state->render_info.VBOs, VBO);
        add_to_unsigned_list(&engine_state->render_info.EBOs, EBO);
        printf("%d Bye\n", engine_state->render_info.EBOs.elt);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
    }
    
    printf("Bonsoir\n");


    

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

    // Définir le mode de rendu (pour le Developpement)
    engine_state->render_info.render_mode = GL_LINE;
    glPolygonMode(GL_FRONT_AND_BACK, engine_state->render_info.render_mode);
}
void update_render_main_menu(st_engine *engine_state){
    
    
    glClearColor(num_to_01(123), num_to_01(12), num_to_01(123), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(engine_state->render_info.shader_program);

    glBindVertexArray(get_by_indice(&engine_state->render_info.VAOs, 0).elt);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
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