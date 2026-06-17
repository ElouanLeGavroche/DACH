#include "../../../include/src_include/Context/Model/model_main_menu_context.h"


void update_logic_main_menu(st_engine *engine_state)
{

}

void init_data_main_menu(st_engine *engine)
{
    // Charger les shaders du context
    const char *vertex_shader_source = load_shader("src/Shaders/main_shader.vert");
    const char *fragment_shader_source = load_shader("src/Shaders/main_shader.frag");

    if(!vertex_shader_source || !fragment_shader_source)
    {
        printf("Attention, certains shaders n'ont pas élé chargé"
        "Le comportement du programme peux-être compromis.\n");
    }
    
    // Charger les élément du menu

    st_tile first_square;
    //st_tile seconde;

    load_file(BASIC_HOUSE_PATH, &first_square);

}