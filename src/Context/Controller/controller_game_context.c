#include "../../../include/src_include/Context/Controller/controller_game_context.h"

struct st_state game_state =
{
    init_game,
    controller_update_logic_game,
    controller_update_render_game
};

void init_game(st_state *state)
{
    printf("début de l'initiation\n");

    // CHARGER LES SHADERS --------------------------------------------------------------------------------------------
    const char *vertex_shader_source = load_shader("src/Shaders/main_shader.vert");
    const char *fragment_shader_source = load_shader("src/Shaders/main_shader.frag");
    
    state->render.nb_shader = 1;
    
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
    

    state->render.nb_mesh = 2;

    // Mallocs --------------------------------------------------------------------------------------------

    state->render.meshs = malloc(sizeof(st_mesh) * state->render.nb_mesh);
    state->render.shader_programs = malloc(sizeof(st_shader) * state->render.nb_shader);
    
    // Initialiser les shaders --------------------------------------------------------------------------------------------
    init_a_loaded_shader(&state->render, vertex_shader_source, fragment_shader_source);

    // Initialiser les éléments 3D --------------------------------------------------------------------------------------------
    init_a_3d_loaded_element(&state->render, &seconde_square, 0);
    init_a_3d_loaded_element(&state->render, &first_square, 1);

    init_render_game(&state->render);
    
    printf("Context jeu initier\n");
}


void controller_update_logic_game(st_engine *engine_state)
{
    update_logic_game(engine_state);
}

void controller_update_render_game(st_render_data *render)
{
    update_render_game(render);
}