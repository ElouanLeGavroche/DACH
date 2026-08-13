#include "../../../include/src_include/Context/Controller/controller_pause_menu_context.h"

int init_pause_menu(st_context *state)
{
    return RES_DONE;
}

void controller_update_logic_pause_menu(st_context *state)
{
    printf("Logique de pause.\n");
}

void controller_update_render_pause_menu(st_render_data *render, double time)
{
    printf("Rendu de pause.\n");
}

st_context* create_pause_menu_context()
{
    struct st_context *main_menu_state = malloc(sizeof(st_context));

    main_menu_state->id = C_MAIN_MENU;
    
    main_menu_state->init_state = init_pause_menu;
    main_menu_state->update_logic_context = controller_update_logic_pause_menu;
    main_menu_state->update_render_context = controller_update_render_pause_menu;

    main_menu_state->politicy.input_bellow = false;
    main_menu_state->politicy.render_bellow = false;
    main_menu_state->politicy.update_bellow = false;

    return main_menu_state;
}