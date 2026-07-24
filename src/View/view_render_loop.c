#include "../../include/src_include/View/view_render_loop.h"

void view_clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
st_mesh init_a_3d_loaded_element(st_mesh_data *elt, int indice)
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
void view_render(st_render_data *render)
{
int i, y;
    /* 
    On va en premier lieu calculer le temps que prend une frame à être fait
    ainsi, la caméra ne dépendant plus de la vitesse du jeu .
    */
    glDepthFunc(GL_LESS);  
    float current_frame = glfwGetTime();
    render->delta_time = current_frame - render->last_time;
    render->last_time = current_frame;

    render->camera.actual_speed = render->camera.speed *render->delta_time;
    
    
    vec3 center;
    pthread_mutex_lock(&render->camera.mutex);
    glm_vec3_sub(render->camera.pos, render->camera.front, center);
    glm_lookat(
        render->camera.pos, 
        center, 
        render->camera.up, 
        render->camera.view
    );
    pthread_mutex_unlock(&render->camera.mutex);

    glClearColor(num_to_01(24), num_to_01(32), num_to_01(61), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(i = 0; i < render->nb_groups; i ++)
    {
        
        switch (render->groups[i].type)
        {
        case RENDER_GROUP_INSTANCED_MESH:
            view_instanced_render(&render->groups[i], &render->camera);
            break;
        
        case RENDER_GROUP_MESH:
            view_normal_render(&render->groups[i]);
            break;
        
        default:
            break;
        }
        
    }
}

void view_billboard_render();

void view_instanced_render(st_render_group *void_group, st_camera *camera)
{
    /* Model */
    mat4 model;
    glm_mat4_identity(model);

    st_instanced_mesh_group *group = (st_instanced_mesh_group*)void_group->data;
    st_render_object *obj = group->shared_render_object;

    glm_translate(model, (vec3){obj->transform.position.x, obj->transform.position.y, obj->transform.position.z});


    /* Application du point de vue */
    int view_loc = glGetUniformLocation(obj->material->shader->shader, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, &camera->view[0][0]);
    
    /* Application de la projection*/
    int proj_loc = glGetUniformLocation(obj->material->shader->shader, "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &camera->projection[0][0]);

    /* application d'une transformation bidon */
    unsigned int transfrom_loc = glGetUniformLocation(obj->material->shader->shader, "transform");;
    glUniformMatrix4fv(transfrom_loc, 1, GL_FALSE, *model);

    glUseProgram(obj->material->shader->shader);
    glBindTexture(GL_TEXTURE_2D, obj->material->texture->id);

    // Lié le VAO
    glBindVertexArray(obj->mesh->VAO);
    
    glDrawElementsInstanced(GL_TRIANGLES, obj->mesh->index_count, GL_UNSIGNED_INT, 0, group->st_instanced.count);
    glBindVertexArray(0);
}

void view_normal_render(st_render_group *group)
{
    unsigned int transform_loc;
    
    // Préparation des info à envoyer au rendu
    mat4 model, proj, trans, view;
    glm_mat4_identity(model);
    glm_mat4_identity(proj);
    glm_mat4_identity(trans);
    glm_mat4_identity(view);

    /* Model */
    glm_rotate(model, (float)glfwGetTime(), (vec3){0.0f, 0.0f, 1.0f});

    /* Projection en perspective de la caméra */
    glm_perspective(glm_rad(45.0f), (float)1280/(float)720, 0.1f, 100.0f, proj);

    /* Modification que l'on apporte au model */
    glm_rotate(trans, (float)glfwGetTime(), (vec3){1.0, 1.0, 1.0});
    glm_scale(trans, (vec3){0.5, 0.5, 0.5});

    /* Gestion de la caméra et de ces déplacement*/
    float radius = 10.0f;
    float cam_x = sin(glfwGetTime()) * radius;
    float cam_z = cos(glfwGetTime()) * radius;

    glm_lookat((vec3){cam_x, 0.0, cam_z}, (vec3){0.0, 0.0, 0.0}, (vec3){0.0, 1.0, 0.0}, view);

    st_mesh_group *mesh_group = group->data;
    int y;
    for(y = 0; y < mesh_group->nb_objects; y ++)
    {
        
        int model_loc = glGetUniformLocation(mesh_group->objects[y].material->shader->shader, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, *model);

        int view_loc = glGetUniformLocation(mesh_group->objects[y].material->shader->shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, *view);

        int proj_loc = glGetUniformLocation(mesh_group->objects[y].material->shader->shader, "projection");
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, *proj);

        transform_loc = glGetUniformLocation(mesh_group->objects[y].material->shader->shader, "transform");
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, *trans);

        // Pour le shader
        glUseProgram(mesh_group->objects[y].material->shader->shader);

        // Pour les texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh_group->objects[y].material->texture->id);

        // Pour les éléments
        glBindVertexArray(mesh_group->objects[y].mesh->VAO);
        glDrawElements(GL_TRIANGLES, mesh_group->objects[y].mesh->index_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}