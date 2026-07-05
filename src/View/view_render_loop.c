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
        return -1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief Cette fonction va me servir à initialiser les différent éléments graphique de la page
 */
st_mesh init_a_3d_loaded_element(st_mesh *elt, int indice)
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

    glBufferData(GL_ARRAY_BUFFER, sizeof(*elt->vert_pos)*elt->vertex_float_count, elt->vert_pos, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*elt->face_indice)*elt->index_count, elt->face_indice, GL_STATIC_DRAW);


    elt->VAO = VAO;
    elt->VBO = VBO;
    elt->EBO = EBO;
    
    // Positition des polygones
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Les couleurs
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // Les UVs
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    return *elt;
}

int init_a_loaded_shader(const char vertex_shader_source[], const char fragment_shader_source[])
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
        printf("Erreur lors de la compilation du Vertex Shader : %s\n", infoLog);
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        printf("Erreur lors de la compilation du Frag Shader : %s\n", infoLog);
    }

    
    shader_program = glCreateProgram();
    
    // On lie le frag et le vert dans un seul prg
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        printf("Erreur lors de la création du programe shader : %s\n", infoLog);
    }
    
    // Une fois lié, l'on peux les supprimer
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

int init_a_loaded_texture(st_image *image)
{
    /* Variables de debug */
    int  success;
    char infoLog[512];

    // GENÉRÉ LES TEXTURES --------------------------------------------------------------------------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // définit les options de la texture actuellement liée
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // charge et génère la texture
    if (image->data != NULL)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glGetProgramiv(texture, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(texture, 512, NULL, infoLog);
            printf("Erreur lors de la création du programe shader : %s\n", infoLog);
        }
    }
    else
    {
        fprintf(stderr, "erreur lors de la création de la texture\n");
    }

    return texture;
}