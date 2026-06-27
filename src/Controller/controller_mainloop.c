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
        
        // Contenu //
        engine_state->stack_context.current_state->update_logic_context(engine_state->stack_context.current_state);
        
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


    // récupéré les entrées //
    int i;
    for(i = 0; i < KEY_NUM; i ++)
    {
        engine_state->stack_context.current_state->inputs.release[i] = false;
    }
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
            //engine_state->context_tool.remove_context(&engine_state->stack_context);
            //engine_state->stack_context.current_state->init_state(engine_state->stack_context.current_state);

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
            new_context(engine_state, new_state);
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

    // Affichage du premier State (TEMP Main_menu)
    engine_state->context_tool.put_context(&engine_state->stack_context, &main_menu_state);

    //Initialiser le contenu de la State
    engine_state->stack_context.current_state->init_state(engine_state->stack_context.current_state);

    // On relie le clavier au nouveau context
    link_input(engine_state);


    // Création des threads et passage de la structure engine
    pthread_create(&logical_thread, NULL, logical_loop, engine_state);

    //Définition des variables pour accorder la clock
    struct timespec ts_start, ts_end;
    double elapsed;

    ////////////////////////////////////////////
    //                                        //
    //                Boucle                  //
    //                                        //
    ////////////////////////////////////////////

    while(engine_state->running && !glfwWindowShouldClose(glfwGetCurrentContext())){
        // Time au début de la boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_start);
        view_clear();
        
        //Actual context
        engine_state->stack_context.current_state->update_render_context(&engine_state->stack_context.current_state->render);
        input_loop(engine_state);

        view_swap();

        //Time fin de boucle
        clock_gettime(CLOCK_MONOTONIC, &ts_end);

        //Gestion de des conditions au calcul d'un nouveau tick
        wait_frame(ts_start, ts_end);

    }

    engine_state->running = false;
    pthread_join(logical_thread, NULL);

    unload_data(engine_state);

    view_close_window();
}

void new_context(st_engine *engine_state, st_state *new_state)
{
    
    // L'on initialise le nouveau context
    new_state->init_state(new_state);

    // L'on envoie le context suivant pour remplacer l'actuel
    engine_state->context_tool.put_context(&engine_state->stack_context, new_state);
    
    // L'on supprime le context suivant qui est déjà placé
    engine_state->stack_context.current_state->ev_next_context = C_NONE;

    // On relie le clavier au nouveau context
    link_input(engine_state);


}

void unload_data(st_engine *engine_state)
{
    // Effacer les données de rendu
    destroy_render_data(&engine_state->stack_context.current_state->render);
    
    // Effacer les données de model
}

void destroy_render_data(st_render_data *render)
{

    if(render == NULL || render->meshs == NULL)
        return;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);

    int i;
    // On détruit tout les éléments de la liste
    for(i = 0; i < render->nb_mesh; i ++)
    {
        glDeleteVertexArrays(1, &render->meshs[i].VAO);
        glDeleteBuffers(1, &render->meshs[i].VBO);
        glDeleteBuffers(1, &render->meshs[i].EBO);

        free(render->meshs[i].face_pos);
        free(render->meshs[i].vert_pos);
    }
    
    for(i = 0; i < render->nb_shader; i ++)
    {
        glDeleteProgram(render->shader_programs[i].shader);
    }
    
    free(render->meshs);
    render->meshs = NULL;
    render->nb_mesh = 0;

    // On reset les données au sein des shaders
    free(render->shader_programs);
    render->shader_programs = NULL;
    render->nb_shader = 0;

    // ça permet de forcer la cg à mettre à jour son utilisation de la mémoire.
    glFinish();

}


void link_input(st_engine *engine_state)
{
    // Liée la strucures des entrée dans la fnêtre pour le callback
    GLFWwindow *window = glfwGetCurrentContext();
    glfwSetWindowUserPointer(window, &engine_state->stack_context.current_state->inputs);
    glfwSetKeyCallback(window, pressed_key_callback);
}