#include "../../include/src_include/Renderer/opengl_renderer.h"

void init_opengl()
{
    /* Activer le test de profondeur */
    glEnable(GL_DEPTH_TEST);
}

/**
 * @brief Cette fonction va me servir à initialiser les différent éléments graphique de la page
 */
st_mesh init_a_3d_loaded_element(st_mesh_data *elt)
{
    st_mesh mesh;
    unsigned int VAO, VBO, EBO;
    // Tampon où l'on stock les sommets
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);  
    glGenBuffers(1, &EBO);
    
    // 1.Attacher le VAO (Vertex Array Object)
    glBindVertexArray(VAO);

    // 2.Mettre les sommet dans le VBO et EBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(*elt->vert_pos)*elt->vertex_count, elt->vert_pos, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*elt->face_indice)*elt->index_count, elt->face_indice, GL_STATIC_DRAW);


    mesh.VAO = VAO;
    mesh.VBO = VBO;
    mesh.EBO = EBO;
    mesh.index_count = elt->index_count;
    mesh.nb_occurences = 0;
    
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

    return mesh;
}

st_mesh init_a_2d_plane(float x, float y, float size_x, float size_y)
{
    st_mesh mesh;
    unsigned int VAO, VBO, EBO;

    float vertices[] = {
        x,  y, 0.0f,                   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        x, y + size_y, 0.0f,           0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        x + size_x, y + size_y, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        x + size_x,  y, 0.0f,           1.0f, 1.0f, 0.0f,   0.0f, 1.0f 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    // Tampon où l'on stock les sommets
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);  
    glGenBuffers(1, &EBO);
    
    // 1.Attacher le VAO (Vertex Array Object)
    glBindVertexArray(VAO);

    // 2.Mettre les sommet dans le VBO et EBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    mesh.VAO = VAO;
    mesh.VBO = VBO;
    mesh.EBO = EBO;
    mesh.index_count = 6;
    mesh.nb_occurences = 0;
    
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

    return mesh;

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
        return RES_ERROR;
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        printf("Erreur lors de la compilation du Frag Shader : %s\n", infoLog);
        return RES_ERROR;
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
        return RES_ERROR;
    }
    
    // Une fois lié, l'on peux les supprimer
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

int init_a_loaded_texture(st_image *image)
{
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
        switch (image->nr_channels)
        {
        case 3:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
            break;
        
        case 4:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
            break;
        default:
            break;
        }
        
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        fprintf(stderr, "erreur lors de la création de la texture\n");
        return -1;
    }

    return texture;
}

void gl_deletes()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

void gl_delete_mesh(st_render_object *object)
{
    glDeleteVertexArrays(1, &object->mesh->VAO);
    glDeleteBuffers(1, &object->mesh->VBO);
    glDeleteBuffers(1, &object->mesh->EBO);
}

void gl_delete_instanced_mesh(st_instanced *mesh)
{
    glDeleteBuffers(1, &mesh->vbo);
}

void gl_delete_texture(unsigned int id)
{
    glDeleteTextures(1, &id);
}

void gl_delete_shader(unsigned int id)
{
    glDeleteProgram(id);
}

void gl_finish()
{
    glFinish();
}

void gl_update_view_port(int width, int height)
{
    glViewport(0, 0, width, height);
}