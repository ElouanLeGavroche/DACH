#include "../../../include/src_include/Context/View/view_main_menu_context.h"
void init_render_main_menu(st_render_data *render)
{

    // On va associé la caméra dans Opengl, car on peut-en avoir besoin dans les callbacks
    GLFWwindow *window = glfwGetCurrentContext();

    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->camera = &render->camera;
}
void update_render_main_menu(st_render_data *render)
{
    int i;
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

    glClearColor(num_to_01(0), num_to_01(0), num_to_01(0), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(i = 0; i < render->nb_groups; i ++)
    {
        st_render_group *group = &render->groups[i];

        switch (render->groups->type)
        {
        case RENDER_GROUP_MESH:
            
            st_mesh_group *mesh_group = group->data;

            int model_loc = glGetUniformLocation(mesh_group->shaders[0].shader, "model");
            glUniformMatrix4fv(model_loc, 1, GL_FALSE, *model);

            int view_loc = glGetUniformLocation(mesh_group->shaders[0].shader, "view");
            glUniformMatrix4fv(view_loc, 1, GL_FALSE, *view);

            int proj_loc = glGetUniformLocation(mesh_group->shaders[0].shader, "projection");
            glUniformMatrix4fv(proj_loc, 1, GL_FALSE, *proj);

            transform_loc = glGetUniformLocation(mesh_group->shaders[0].shader, "transform");
            glUniformMatrix4fv(transform_loc, 1, GL_FALSE, *trans);
            
            render_mesh_group(mesh_group);
            break;
        
        default:
            break;
        }
    }
    
}
