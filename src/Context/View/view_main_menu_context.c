#include "../../../include/src_include/Context/View/view_main_menu_context.h"


void init_render(st_engine *engine_state){

    const char *vertex_shader_source = load_shader("../../Shaders/main_shader.vert");
    const char *fragment_shader_source = load_shader("../../Shaders/main_shader.frag");
    const char *fragment_shader_source_2 = load_shader("../../Shaders/main_menu_shader.frag");


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

    float second_square[] = {
        -0.9f,  0.9f, 0.0f,  // top right
        -0.9f, 0.6f, 0.0f,  // bottom right
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
    
    engine_state->render_info.VAOs.elt = EMPTY_LIST;
    engine_state->render_info.VBOs.elt = EMPTY_LIST;
    engine_state->render_info.EBOs.elt = EMPTY_LIST;

    engine_state->render_info.shader_programs.elt = EMPTY_LIST;


    int i;
    for(i = 0; i < 2; i ++)
    {
        unsigned int VAO, VBO, EBO;
        unsigned int vertex_shader, fragment_shader, shader_program;
        
        // Tampon où l'on stock les sommets
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);  
        glGenBuffers(1, &EBO);

        // 1.Attacher le VAO (Vertex Array Object)
        glBindVertexArray(VAO);

        // 2.Mettre les sommet dans le VBO et EBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        if(i == 0){
            glBufferData(GL_ARRAY_BUFFER, sizeof(first_square), first_square, GL_STATIC_DRAW);
        }
        else{
            glBufferData(GL_ARRAY_BUFFER, sizeof(second_square), second_square, GL_STATIC_DRAW);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        add_to_unsigned_list(&engine_state->render_info.VAOs, VAO);
        add_to_unsigned_list(&engine_state->render_info.VBOs, VBO);
        add_to_unsigned_list(&engine_state->render_info.EBOs, EBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 

        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        
        glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
        glCompileShader(vertex_shader);
        
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        if(i == 0){
            glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);    
        }
        else{
        glShaderSource(fragment_shader, 1, &fragment_shader_source_2, NULL);
        }
        glCompileShader(fragment_shader);

        shader_program = glCreateProgram();
        
        // On lie le frag et le vert dans un seul prg
        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);
        
        // Une fois lié, l'on peux les supprimer
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        add_to_unsigned_list(&engine_state->render_info.shader_programs, shader_program);
    }
    
    printf("Bonsoir\n");


    // Définir le mode de rendu (pour le Developpement)
    engine_state->render_info.render_mode = GL_LINE;
    glPolygonMode(GL_FRONT_AND_BACK, engine_state->render_info.render_mode);
}
void update_render_main_menu(st_engine *engine_state){
    
    
    glClearColor(num_to_01(123), num_to_01(12), num_to_01(123), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(get_by_indice(&engine_state->render_info.shader_programs, 0).elt);

    glBindVertexArray(get_by_indice(&engine_state->render_info.VAOs, 0).elt);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glUseProgram(get_by_indice(&engine_state->render_info.shader_programs, 1).elt);
    
    glBindVertexArray(get_by_indice(&engine_state->render_info.VAOs, 1).elt);

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