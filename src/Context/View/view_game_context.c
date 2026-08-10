#include "../../../include/src_include/Context/View/view_game_context.h"


void init_render_game(st_render_data *render)
{

    render->nb_groups = 0;
    render->nb_total_groups = 0;
    
    //init_game_camera(&render->camera);


    // On va associé la caméra dans Opengl, car on peut-en avoir besoin dans les callbacks
    GLFWwindow *window = glfwGetCurrentContext();

    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->camera = &render->camera; 
}

void create_an_instance_GPU(st_instanced *instance, mat4 *model, int amount)
{
    int i;
    unsigned int instance_vbo;
    glGenBuffers(1, &instance_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(mat4), &model[0], GL_STATIC_DRAW);

    // On va diviser le model en 4 partie pour l'envoier au GPU
    // via les in layout, et c'est lui qui s'occupera de les reformer

    for(i = 0; i < 4; i ++)
    {
        
        glEnableVertexAttribArray(3 + i);
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*) (i* sizeof(vec4)) );
        glVertexAttribDivisor(3 + i, 1);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    instance->vbo = instance_vbo;
}

void update_render_game(st_render_data *render)
{
    render_context(render);
}