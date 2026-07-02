#include "../../../include/src_include/Context/Controller/controller_main_menu_context.h"

struct st_state main_menu_state =
{
    init_menu,
    controller_update_logic_main_menu,
    controller_update_render_main_menu,
};

int init_menu(st_state *state)
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
    st_mesh first_square = {0};
    load_file(BASIC_HOUSE_PATH, &first_square);

    st_mesh seconde_square = {0};
    load_file(BASIC_TILE_PATH, &seconde_square);

    state->render.nb_mesh = 2;   

    // CHARGER LES TEXTURES DES ELEMENTS --------------------------------------------------------------------------------------------
    st_image first_square_texture = load_texture("ressources/images/grass_test.jpg", 736, 552, 0);

    // Initialiser les Texuture des elements --------------------------------------------------------------------------------------------
    first_square.texture_id = init_a_loaded_texture(&first_square_texture);
    seconde_square.texture_id = init_a_loaded_texture(&first_square_texture);
    stbi_image_free(first_square_texture.data);


    // Mallocs --------------------------------------------------------------------------------------------

    state->render.meshs = malloc(sizeof(st_mesh) * state->render.nb_mesh);
    state->render.shader_programs = malloc(sizeof(st_shader) * state->render.nb_shader);

    // Initialiser les shaders --------------------------------------------------------------------------------------------
    // Faire une fonction propre pour les charger individuellement ou par liste
    init_a_loaded_shader(&state->render, vertex_shader_source, fragment_shader_source);
    
    // Libéré les shader qui sont compilé côté GPU à présent
    free((void *)vertex_shader_source);
    free((void *)fragment_shader_source);
    
    glUseProgram(state->render.shader_programs[0].shader);
    glUniform1i(glGetUniformLocation(state->render.shader_programs[0].shader, "our_texture"), 0);

    // Initialiser les éléments 3D --------------------------------------------------------------------------------------------
    init_a_3d_loaded_element(&state->render, &seconde_square, 0);
    init_a_3d_loaded_element(&state->render, &first_square, 1);

    // Initialiser la perspective --------------------------------------------------------------------------------------------
    init_render_main_menu(&state->render);

    // Initialiser le model --------------------------------------------------------------------------------------------
    init_data_main_menu(state);

    printf("Context menu initier\n");
    return DONE;
}


void controller_update_logic_main_menu(st_state *state)
{
    update_logic_main_menu(state);
}

void controller_update_render_main_menu(st_render_data *render)
{
    update_render_main_menu(render);
}