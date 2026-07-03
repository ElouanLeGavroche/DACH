#include "../../include/src_include/Model/model_init.h"

int load_screen_data(st_loaded_windows_data *screen_data, st_engine *engine_state)
{
    // Fichier    
    FILE *fp;
    char buffer[1024] = {'\0'};

    // Structures des différents éléments stocké dans le JSON
    struct json_object *parsed_json;
    struct json_object *size_x;
    struct json_object *size_y;
    struct json_object *frame_rate;
    struct json_object *initial_context;

    // Variables des valeur à récuperer
    int size_x_value;
    int size_y_value;
    int frame_rate_value;
    const char *initial_context_value = NULL;

    // Initialisation des premières variables du moteur
    engine_state->running = true;


    // Initialisation des outils de context
    engine_state->context_tool.put_context = put_context;
    engine_state->context_tool.remove_context = remove_context;

    engine_state->stack_context.level_of_depth = 0;
    engine_state->stack_context.current_state = NULL;

    fp = fopen(PATH_LOAD_GAME_DATA, "r");
    if(fp == NULL){
        printf("Fichier non trouvé\n");
        return EXIT_FAILURE;
    }
    else{
        printf("fichier ouvert\n");
    }

    fread(buffer, 1024, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    // Parser la struct dans les sous structures adéquat 
    json_object_object_get_ex(parsed_json, "size_x", &size_x);
    json_object_object_get_ex(parsed_json, "size_y", &size_y);
    json_object_object_get_ex(parsed_json, "frame_rate", &frame_rate);

    size_x_value = json_object_get_int(size_x);
    size_y_value = json_object_get_int(size_y);
    frame_rate_value = json_object_get_int(frame_rate);

    
    //Vider la mémoire
    json_object_put(parsed_json);

    // Vérification de la cohérence des données récuperer
    if
    (
        !(
        (7680 > size_x_value && size_x_value > 352) &&
        (4320 > size_y_value && size_y_value > 240) &&
        (360 > frame_rate_value && frame_rate_value > 20)
        )    
    )
    
    {
        printf(" Valeur incohérente ! \n mise en place de valeur par défault : \n x:%d \n y:%d \n fps:%d \n",
        SCREEN_WITH_DEFAULT, SCREEN_HEIGHT_DEFAULT, SCREEN_FRAME_RATE_DEFAUL);
        
        size_x_value = SCREEN_WITH_DEFAULT;
        size_y_value = SCREEN_HEIGHT_DEFAULT;
        frame_rate_value = SCREEN_FRAME_RATE_DEFAUL;
    }
    // Allocation des informations de la fenêtre
    screen_data->size_x = size_x_value;
    screen_data->size_y = size_y_value;
    screen_data->frame_rate = frame_rate_value;


    return DONE;
}


void create_group()
{
    
}