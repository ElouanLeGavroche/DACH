#include "../../include/src_include/Core/context_request.h"

void context_request(st_engine *engine_state){
    // Ce tampon permet de savoir si le jeu est revenu à un etat entérieur
    // Et donc de recharger les éléments qui lui y étais associé
    int res = RES_DONE;
    st_context_request *request = &engine_state->stack_context.current_state->request;
    int action = request->action;
    
    switch (action)
    {
    case CONTEXT_ACTION_PUSH:
        st_context *new_state;
        new_state = &game_state; 

        res = engine_state->context_tool.create_context(new_state);
        if(res == RES_ERROR)
        {
            // Gestion de l'err&engine_state->stack_context.current_state->ev_next_contexteur
            engine_state->running = false;
        }
        engine_state->context_tool.push_context(new_state, &engine_state->stack_context);
        //new_state = request->target;
        break;

    case CONTEXT_ACTION_POP:
        
        destroy_render_data(&engine_state->stack_context.current_state->render);
        engine_state->context_tool.exit_context(&engine_state->stack_context);
        // On relie le clavier au nouveau context
        link_input(engine_state->stack_context.current_state);
        link_mouse(engine_state->stack_context.current_state);
        
        break;
    
    case CONTEXT_ACTION_QUIT:
        while(engine_state->stack_context.current_state != NULL)
        {
            destroy_render_data(&engine_state->stack_context.current_state->render);
            engine_state->context_tool.exit_context(&engine_state->stack_context);
        }
        
        engine_state->running = false;
        break;

    default:
        break;
    }
        

    request->action = CONTEXT_ACTION_NONE;
    request->target = C_NONE;

}


void destroy_render_data(st_render_data *render)
{
    if(render == NULL || render->groups == NULL)
            return;
    int i, y;
    int tamp_nb_object;
    int tamp_nb_group;

    st_mesh_group *mesh_group;
    st_instanced_mesh_group *instanced_mesh_group;
    st_render_object *object;

    printf("Début de libération de la mémoire de l'ancien context.\n");

    gl_deletes();

    tamp_nb_group = render->nb_groups;
    for(i = 0; i < tamp_nb_group; i ++)
    {
        
        // On récupère toujours le premier, car l'ancien premier à été supprimer
        st_render_group *group = &render->groups[0];
        
        switch (group->type)
        {
        case RENDER_GROUP_MESH:
            // On récupère les data avec le type mesh groupe
            mesh_group = group->data;
            tamp_nb_object = mesh_group->nb_objects;

            for(y = 0; y < tamp_nb_object; y ++)
            {
                // On supprime toujours le premier élément
                object = &mesh_group->objects[0];
                printf("Suppresion de l'élément : %d, éléments free : %d/%d.\n", object->id, y, tamp_nb_object - 1);

                references_object_test(object);
                
                free(object->material);
                object->material = NULL;

                free(object->mesh);
                object->mesh = NULL;
                
                group->tables->remove_element(mesh_group, object->id);
            }
            
            // Quelques vérification si toutes les suppression on bien été faite
            if(mesh_group->nb_objects != 0)
            {
                fprintf(stderr, "Attention certain élément n'ont pas été supprimer.\n");
            }
            if(mesh_group->objects != NULL)
            {
                fprintf(stderr, "Le groupe n'a pas été free correctement.\n");
            }

            break;
        case RENDER_GROUP_INSTANCED_MESH:
            
            // On récupère les data avec le type mesh groupe
            instanced_mesh_group = group->data;
            references_object_test(instanced_mesh_group->shared_render_object);
            
            free(instanced_mesh_group->shared_render_object->material);
            free(instanced_mesh_group->shared_render_object->mesh);
            
            free(instanced_mesh_group->shared_render_object);
            
            glDeleteBuffers(1, &instanced_mesh_group->st_instanced.vbo);
            free(instanced_mesh_group->st_instanced.cpu_data);
            
            break;
        
        default:
            fprintf(stderr, "Type du groupe inconnu.\n");
            break;
        }
        
        // On supprime le groupe type
        free(group->data);
        // On supprime les tables du groupe
        free(group->tables);
        // On supprime le groupe
        
        remove_group(render, group->ID);
        
    }
    free(render->groups);
    render->groups = NULL;
    render->nb_groups = 0;

    // ça permet de forcer la cg à mettre à jour son utilisation de la mémoire.
    gl_finish();
    printf("Datas supprimer.\n");

}


void references_object_test(st_render_object *object)
{
    object->material->shader->nb_occurences --;
    object->material->texture->nb_occurences --;
    object->mesh->nb_occurences --;
    
    // On supprime les données OpenGL
    // Si c'est le dernier object à avoir l'occurence d'un mesh, alors c'est lui qui le supprime
    if(object->mesh->nb_occurences == 0)
    {
        gl_delete_mesh(object);
        object->mesh->index_count = 0;
        
    }
    // Si c'est le dernier object à avoir l'occurence d'une texture alors c'est lui qui le supprime
    if(object->material->texture->nb_occurences == 0)
    {
        gl_delete_texture(object->material->texture->id);
        free(object->material->texture);
    }
    // Si c'est le dernier object à avoir l'occurence d'un shader, alors c'est lui qui le supprime
    if(object->material->shader->nb_occurences == 0)
    {
        gl_delete_shader(object->material->shader->shader);
        free(object->material->shader);
    }
}