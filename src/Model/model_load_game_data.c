#include "../../include/src_include/Model/model_load_game_data.h"

int load_screen_data(t_loaded_windows_data *screen_data)
{
    // Buffer pour la lecture
    t_window_info data;
    
    // Buffer du séparator, sert avant tout à vérifier qu'il n'y à pas de décalage
    char separator;

    // Pour savoir le nombre de bytes lu
    size_t nb_byte_readed;
    
    //Fichier ouvert
    int fd;

    int i;
    int res;
    bool passed = false;

    while(passed != true){
        printf("Chargement des données de l'écran --- \n");
        
        // Ouverture du fichier + vérification de réussite
        fd = open(PATH_LOAD_GAME_DATA, O_RDONLY);
        if (fd < 0)
        {
            printf("Erreur lors de l'ouverture du fichier\n");
            return ERROR;
        }

        //Lire le fichier 4 byte par 4 bytes pour chopper les nombre voulus
        for (i = 0; i < NB_DATA_TO_LOAD_FOR_SCREEN; i++)
        {
            nb_byte_readed = read(fd, data, READ_SIZE);

            // Si le nb de chiffre lu ne correspont pas, mettre fin à la boucle
            if (nb_byte_readed < READ_SIZE)
            {
                printf("Erreur lors de la lecture\n");
                i = NB_DATA_TO_LOAD_FOR_SCREEN + 1;
            }
            else{

                switch (i)
                {
                case 0:
                    screen_data->size_x = atoi(data);
                    break;
                case 1:
                    screen_data->size_y = atoi(data);
                    break;
                case 2:
                    screen_data->frame_rate = atof(data);
                    break;
                default:
                    break;
                }
            
                nb_byte_readed = read(fd, &separator, DEFAULT_READ_SIZE);

                // Vérifie que la lecture c'est bien passé + vérifie que le séparator est à ça place 
                if (nb_byte_readed != DEFAULT_READ_SIZE || separator == FILE_SEPARATOR != 1)
                {
                    printf("Erreur lors de la lecture du séparateur\n");
                    i = NB_DATA_TO_LOAD_FOR_SCREEN + 1;
                }
            
            }
        }

        // Si le format à mal été reconnu plus haut, l'on va ici lancer la fonction
        // Pour réparer le fichier. (retourne une erreur si elle n'a pas réussi)
        if(i  == NB_DATA_TO_LOAD_FOR_SCREEN + 2){
            if(repair_window_info() == ERROR){
                        
                printf("Tentative de réparation échoué.\n");
                return ERROR;
            }
            else{
                printf("Fichier réparer, configuration par défault affecter\n");
            }
        }
        else{
            passed = true;
        }
    }
    close(fd);
    printf("Chargées --- \n");
    return DONE;
}