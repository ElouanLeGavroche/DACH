#include "../../include/src_include/View/view_render_loop.h"

void view_clear(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void view_swap(){
    // Récupéré le context openGL
    GLFWwindow *window = glfwGetCurrentContext();

    // Actualisation du swap
    glfwSwapBuffers(window);
}

void view_close_window(){
    GLFWwindow *window = glfwGetCurrentContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
}

int window_should_close(){
    if (glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * @brief Cette fonction va me servir à initialiser les différent éléments graphique de la page
 */
void init_data_view_context()
{

    /*
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
    */
}