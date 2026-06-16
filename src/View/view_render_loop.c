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
void init_a_3d_loaded_element(st_engine *engine_state, st_tile *elt)
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
    
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(elt->vert_pos)*elt->nb_vert, elt->vert_pos, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*elt->face_pos)*elt->nb_face, elt->face_pos, GL_STATIC_DRAW);

    put_unsigned_int_lst(&engine_state->render.VAOs, VAO);
    put_unsigned_int_lst(&engine_state->render.VBOs, VBO);
    put_unsigned_int_lst(&engine_state->render.EBOs, EBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // Définir le mode de rendu (pour le Developpement)
    engine_state->render.render_mode = GL_LINE;
    glPolygonMode(GL_FRONT_AND_BACK, engine_state->render.render_mode);

}

void init_a_loaded_shader(st_engine *engine_state, const char vertex_shader_source[], const char fragment_shader_source[])
{
    /* Variables de debug */
    int  success;
    char infoLog[512];

    unsigned int vertex_shader, fragment_shader, shader_program;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        printf("Erreur lors de la compilation du Vertex Shader\n");
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        printf("Erreur lors de la compilation du Frag Shader\n");
    }


    shader_program = glCreateProgram();

    // On lie le frag et le vert dans un seul prg
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        printf("Erreur lors de la création du programe shader\n");
    }

    // Une fois lié, l'on peux les supprimer
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    put_unsigned_int_lst(&engine_state->render.shader_programs, shader_program);
}