#include "../../../include/src_include/Context/Controller/controller_main_menu_context.h"

struct st_state main_menu_state =
{
    init_menu,
    input_context_main_menu,
    controller_update_logic_main_menu,
    controller_update_render_main_menu
};

void init_menu(st_engine *engine_state)
{
    printf("début de l'initiation\n");

    // CHARGER LES SHADERS --------------------------------------------------------------------------------------------
    const char *vertex_shader_source = load_shader("src/Shaders/main_shader.vert");
    const char *fragment_shader_source = load_shader("src/Shaders/main_shader.frag");
    
    // ""Gestion de l'erreur - lmao""
    if(!vertex_shader_source || !fragment_shader_source)
    {
        printf("Attention, certains shaders n'ont pas élé chargé"
        "Le comportement du programme peux-être compromis.\n");
    }
    
    // CHARGER LES ELEMENTS --------------------------------------------------------------------------------------------
    st_mesh first_square;
    load_file(BASIC_HOUSE_PATH, &first_square);

    st_mesh seconde_square;
    load_file(BASIC_TILE_PATH, &seconde_square);

    
    
    // Initialiser le rendu --------------------------------------------------------------------------------------------
    
    init_unsigned_int_lst(&engine_state->render.VAOs);
    init_unsigned_int_lst(&engine_state->render.VBOs);
    init_unsigned_int_lst(&engine_state->render.EBOs);
    init_unsigned_int_lst(&engine_state->render.shader_programs);


    // Initialiser les shaders --------------------------------------------------------------------------------------------
    // Faire une fonction propre pour les charger individuellement ou par liste
    init_a_loaded_shader(engine_state, vertex_shader_source, fragment_shader_source);
    

    // Initialiser les éléments 3D --------------------------------------------------------------------------------------------
    init_mesh(engine_state, first_square);
    init_mesh(engine_state, seconde_square);



    // Libéré les shader qui sont compilé côté GPU à présent
    free((void *)vertex_shader_source);
    free((void *)fragment_shader_source);

    printf("Context menu initier\n");
}

void input_context_main_menu(st_engine *engine_state)
{
    // Système temporaire pour traiter les entrées
    if(engine_state->input.escape == true)
    {  
        engine_state->running = false;
    }
    else if(engine_state->input.up_arrow == true)
    {
        engine_state->next_state = &game_state;
    }
    else if(engine_state->input.down_arrow == true)
    {
        engine_state->context_tool.remove_context(&engine_state->stack_context);
    }
    else if(engine_state->input.enter)
    {
        change_render_mode(engine_state);
    }

}

void controller_update_logic_main_menu(st_engine *engine_state)
{
    update_logic_main_menu(engine_state);
}

void controller_update_render_main_menu(st_engine *engine_state)
{
    update_render_main_menu(engine_state);
}