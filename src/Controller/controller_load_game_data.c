#include "../../include/src_include/Controller/controller_load_game_data.h"

int c_load_screen_data(t_loaded_windows_data *data){
    int res;

    res = load_screen_data(data);
    if(res == ERROR){
        printf("Erreur dans la fonction de chargement des paramètre d'écran\n");
        return ERROR;
    }
    return DONE;
}
