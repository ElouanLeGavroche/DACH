#include "../../include/src_include/Controller/controller_mainloop.h"

void *logical_loop(void *data_engine)
{
    // Partie Logique
    st_engine *engine_state = data_engine;
    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;
    // 
    // Partie Model
    while(engine_state->running)
    {
        //Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);
        
        pthread_mutex_lock(&engine_state->context_mutex);
        // Contenu //
        engine_state->stack_context.current_state->update_logic_context(engine_state->stack_context.current_state);
        
        pthread_mutex_unlock(&engine_state->context_mutex);

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_tick(ts_start, ts_end);
    }

    printf("Thread logique mené à bien\n");
}

void input_loop(st_engine *engine_state){
    // Ce tampon permet de savoir si le jeu est revenu à un etat entérieur
    // Et donc de recharger les éléments qui lui y étais associé
    int level_tampon = engine_state->stack_context.level_of_depth;
    int res = DONE;

    // récupéré les entrées //

    glfwPollEvents();
    
    
    if(engine_state->stack_context.current_state->ev_must_close == true)
    {
        engine_state->running = false;
    }
    if(engine_state->stack_context.current_state->ev_next_context != C_NONE)
    {
        st_state *new_state;
        atomic_int *who = &engine_state->stack_context.current_state->ev_next_context;
        
        // L'on va observer vers quelle context évoluer
        switch (*who)
        {
        case C_BACK:

            unload_data(engine_state);
            st_state *old_state = engine_state->stack_context.current_state;
            
            engine_state->stack_context.current_state = old_state->upper;
            engine_state->stack_context.level_of_depth --;

            old_state->upper = NULL;
            level_tampon = engine_state->stack_context.level_of_depth;

            // On relie le clavier au nouveau context
            link_input(engine_state);

            break;
        case C_GAME:
            new_state = &game_state;
            break;

        case C_MAIN_MENU:
            new_state = &main_menu_state;
            break;
        
        default:
            fprintf(stderr, "Context inconnu\n");
            break;
        }
        
        // Si le nouveau context est l'ancien, pas la peine d'en crée un nouveau, ce serai con.
        if(*who != C_BACK)
        {
            res = new_context(engine_state, new_state);
            if(res == ERROR)
            {
                // Gestion de l'erreur
                engine_state->running = false;
            }

            level_tampon = engine_state->stack_context.level_of_depth;
        }
        // On reset la valeur, sinon on retourne en boucle sur le context précédent
        *who = C_NONE;
    }

}


/**
 * @brief Simplement la mainloop qui tourne sur le thread principale et qui orchestre le rendu
 * @param engin_state le moteur
 */
void controller_mainloop_management(st_engine *engine_state){

    // Thread qui tournera en parralèlle pour la logique. En outre
    // Il ne s'actualisera que 20 fois par seconde au le de 60
    // comme les graphismes
    pthread_t logical_thread;
    // Varibiable pour les erreurs
    int res;

    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;

    // On charge le premier context
    res = new_context(engine_state, &main_menu_state);
    if(res != ERROR)
    {
        // Pas la peine de crée le nouveau thread si le menu n'a pas bien charger.

        // Création des threads et passage de la structure engine
        pthread_create(&logical_thread, NULL, logical_loop, engine_state);
        
            ////////////////////////////////////////////
            //                                        //
            //                Boucle                  //
            //                                        //
            ////////////////////////////////////////////

        while(engine_state->running && window_should_close() != -1){
            // Time au début de la boucle
            clock_gettime(CLOCK_MONOTONIC, &ts_start);
            view_clear();
            
            pthread_mutex_lock(&engine_state->context_mutex);

            //Actual context
            engine_state->stack_context.current_state->update_render_context(&engine_state->stack_context.current_state->render);
            input_loop(engine_state);

            pthread_mutex_unlock(&engine_state->context_mutex);
            view_swap();

            //Time fin de boucle
            clock_gettime(CLOCK_MONOTONIC, &ts_end);

            //Gestion de des conditions au calcul d'un nouveau tick
            wait_frame(ts_start, ts_end);

        }
        engine_state->running = false;
        pthread_join(logical_thread, NULL);
        unload_data(engine_state);
    }

    view_close_window();
}

int new_context(st_engine *engine_state, st_state *new_state)
{
    int res;

    // L'on initialise le nouveau context
    res = new_state->init_state(new_state);
    if(res == ERROR)
    {
        printf("Erreur lors de l'initialisation du context\n");
        return ERROR;
    }

    // L'on envoie le context suivant pour remplacer l'actuel
    engine_state->context_tool.put_context(&engine_state->stack_context, new_state);
    engine_state->stack_context.current_state->ev_next_context = C_NONE;
    // On relie le clavier au nouveau context
    link_input(engine_state);
    return DONE;

}

void unload_data(st_engine *engine_state)
{
    // Effacer les données de rendu
    destroy_render_data(&engine_state->stack_context.current_state->render);

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

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
    
    tamp_nb_group = render->nb_groups;
    for(i = 0; i < tamp_nb_group; i ++)
    {
        // On récupère le group lui même pour avoir des lignes plus lisible
        st_render_group *group = &render->groups[i];
        
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
    glFinish();

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
        glDeleteVertexArrays(1, &object->mesh->VAO);
        glDeleteBuffers(1, &object->mesh->VBO);
        glDeleteBuffers(1, &object->mesh->EBO);
        object->mesh->index_count = 0;
        
    }
    // Si c'est le dernier object à avoir l'occurence d'une texture alors c'est lui qui le supprime
    if(object->material->texture->nb_occurences == 0)
    {
        glDeleteTextures(1, &object->material->texture->id);
        free(object->material->texture);
    }
    // Si c'est le dernier object à avoir l'occurence d'un shader, alors c'est lui qui le supprime
    if(object->material->shader->nb_occurences == 0)
    {
        glDeleteProgram(object->material->shader->shader);
        free(object->material->shader);
    }
}

/**
 * @brief Cette fonction permet de lié le callback au context actuel, 
 * il est important de toujours l'initialiser à chaque nouveau context.
 */
void link_input(st_engine *engine_state)
{
    // Liée la strucures des entrée dans la fenêtre pour le callback
    GLFWwindow *window = glfwGetCurrentContext();
    st_window_user_data *data = glfwGetWindowUserPointer(window);
    data->input = &engine_state->stack_context.current_state->inputs;
    
    glfwSetKeyCallback(window, pressed_key_callback);
  
}
