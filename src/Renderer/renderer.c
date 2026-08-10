#include "../../include/src_include/Renderer/renderer.h"

void render_context(st_render_data *render)
{
    int i;
    unsigned int transform_loc;
    // Préparation des info à envoyer au rendu
    mat4 model, proj, trans, view;
    glm_mat4_identity(model);
    glm_mat4_identity(proj);
    glm_mat4_identity(trans);
    glm_mat4_identity(view);

    float current_frame = get_glfw_time();
    render->delta_time = current_frame - render->last_time;
    render->last_time = current_frame;

    render->camera.camera_speed(&render->camera, render->delta_time);
    render->camera.look(&render->camera);
    render->camera.update_ortho(&render->camera);

    glDepthFunc(GL_LESS);
    glClearColor(num_to_01(0), num_to_01(0), num_to_01(0), 1.0f);
    
    for(i = 0; i < render->nb_groups; i ++)
    {
        st_render_group *group = &render->groups[i];

        switch (group->type)
        {
        case RENDER_GROUP_MESH:
            st_mesh_group *mesh_group = group->data;
            int y;
            for(y = 0; y < mesh_group->nb_objects; y ++)
            {
                // Pour le shader
                glUseProgram(mesh_group->objects[y].material->shader->shader);
                
                int model_loc = glGetUniformLocation(mesh_group->objects[y].material->shader->shader, "model");
                glUniformMatrix4fv(model_loc, 1, GL_FALSE, *model);

                int view_loc = glGetUniformLocation(mesh_group->objects[y].material->shader->shader, "view");
                glUniformMatrix4fv(view_loc, 1, GL_FALSE, *view);

                int proj_loc = glGetUniformLocation(mesh_group->objects[y].material->shader->shader, "projection");
                glUniformMatrix4fv(proj_loc, 1, GL_FALSE, *proj);

                transform_loc = glGetUniformLocation(mesh_group->objects[y].material->shader->shader, "transform");
                glUniformMatrix4fv(transform_loc, 1, GL_FALSE, *trans);

                // Pour les texture
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, mesh_group->objects[y].material->texture->id);

                // Pour les éléments
                glBindVertexArray(mesh_group->objects[y].mesh->VAO);
                glDrawElements(GL_TRIANGLES, mesh_group->objects[y].mesh->index_count, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
            }
        break;

        case RENDER_GROUP_INSTANCED_MESH:
            
            st_instanced_mesh_group *inst_group = (st_instanced_mesh_group*)render->groups[i].data;
            st_render_object *obj = inst_group->shared_render_object;

            glUseProgram(obj->material->shader->shader);
            glBindTexture(GL_TEXTURE_2D, obj->material->texture->id);

            /* Application du point de vue */
            int view_loc = glGetUniformLocation(obj->material->shader->shader, "view");
            glUniformMatrix4fv(view_loc, 1, GL_FALSE, &render->camera.view[0][0]);
            
            /* Application de la projection*/
            int proj_loc = glGetUniformLocation(obj->material->shader->shader, "projection");
            glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &render->camera.projection[0][0]);

            /* application d'une transformation bidon */
            unsigned int transfrom_loc = glGetUniformLocation(obj->material->shader->shader, "transform");;
            glUniformMatrix4fv(transfrom_loc, 1, GL_FALSE, *model);

            // Lié le VAO
            glBindVertexArray(obj->mesh->VAO);
            
            glDrawElementsInstanced(GL_TRIANGLES, obj->mesh->index_count, GL_UNSIGNED_INT, 0, inst_group->st_instanced.count);
            glBindVertexArray(0);
            
        break;
        
        default:
            break;
        }
    }
    
}
