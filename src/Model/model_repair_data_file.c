/**
 * @brief Ce code sert à vérifier l'intégrité des fichiers data et de les 
 * remettre au bon format en cas de problème
 */
#include "../../include/src_include/Model/model_repair_data_file.h"

int repair_window_info(){
    
    int fd;
    size_t nb_byte_ecrit;
    /*
    * Format souhaiter
    * XXXX;YYYY;FFFF
    */

    fd = open(PATH_LOAD_GAME_DATA, O_WRONLY);
    if (fd < 0)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        fd = open(PATH_LOAD_GAME_DATA, O_CREAT);
        
        if(fd < 0)
        {
            printf("Erreur lors de la création du fichier\n");
            return ERROR;
        }
        
    }

    nb_byte_ecrit = write(fd, WIN_INF_FORMAT_WITH_DEFAULT_VALUE, sizeof(WIN_INF_FORMAT_WITH_DEFAULT_VALUE)-1);
    // Laissez l'autre code s'occuper de l'affichage en cas d'erreur
    if(nb_byte_ecrit != sizeof(WIN_INF_FORMAT_WITH_DEFAULT_VALUE)-1){
        return ERROR;
    }
    return DONE;

}