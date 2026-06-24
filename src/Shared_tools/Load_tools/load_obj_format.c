#include "../../../include/src_include/Shared_tools/Load_tools/load_obj_format.h"

int load_file(char *path, st_mesh *tile)
{
    /* Variables pour la gestion du fichier */
    FILE *file = NULL;
    char *line = NULL;

    size_t cap = 0;


    /* */
    tile->nb_vert = 0;
    tile->nb_face = 0;
    
    if(open_obj_file(&file, path) != -1)
    {
        if (ferror(file))
        {
            fprintf(stderr, "Erreur lors de la lecture du document\n");
        }
        else
        {
            while (getline(&line, &cap, file) != -1)
            {

                // Sert à savoir combien il y à de vert et de frag avant le malloc
                
                if(line[0] == 'v' && line[1] == ' ')
                { 
                    int y = 0;
                    while(line[y] != '\0' && line[y] != '\n')
                    {
                        if(line[y] == ' ')
                        {
                            tile->nb_vert ++;
                        } 
                        y ++;
                    }
                }
                else if(line[0] == 'f' && line[1] == ' ')
                {
                    int y = 0;
                    while(line[y] != '\0' && line[y] != '\n')
                    {
                        if(line[y] == ' ')
                        {
                            tile->nb_face ++;
                        }
                        y ++;
                            
                    }
                }
                
            }
            fclose(file);
        }


        tile->face_pos = malloc(sizeof(int) * tile->nb_face);
        if(tile->face_pos == NULL)
        {
            free(line);
            return -1;
        }
        else
        {
            tile->vert_pos = malloc(sizeof(float) * tile->nb_vert);
            if(tile->vert_pos == NULL)
            {
                free(line);
                return -1;
            }
        }
        
        if(open_obj_file(&file, path) != -1)
        {
            // indice de où se trouve la boucle actuellement dans les deux listes
            int i_v = 0;
            int i_f = 0;
            line = NULL;

            while (getline(&line, &cap, file) != -1)
            {

                if (ferror(file))
                {
                    fprintf(stderr, "Erreur lors de la lecture du document\n");
                }
                else
                {  
                    // On vérifie la première lettre de la ligne, si c'est un v, on analyse pour les vetrex
                    // Si c'est un f, on regarde avec les face
                    if(line[1] == ' ')
                    {
                        if(line[0] == 'v') 
                        { 
                            i_v = parse_vertext(line, tile, i_v); 
                        }
                        else if(line[0] == 'f') 
                        {
                            i_f = parse_face(line, tile, i_f); 
                        }
                    }

                }

            }
        }
    }
    if(file != NULL)
        fclose(file);

    if(line != NULL)
        free(line);
    return 0;
}

int open_obj_file(FILE **file, char *path)
{
    int err;

    // ouverture du document + gestion des erreurs
    *file = fopen(path, "r");
    if (*file == NULL)
    {
        err = errno;
        fprintf(stderr, "fopen à échoué : ");

        if (err == EACCES)
        {
            fprintf(stderr, "Le programe n'a pas les permission pour ouvrir le fichier.\n");
        }
        else if (err == ENOENT)
        {
            fprintf(stderr, "Le programe n'a pas trouvé le fichier demandé.\n");
            fprintf(stderr, "Chemin parcourus %s.\n", path);
        }

        return -1;
    }
    return 0;
}
int parse_vertext(char line[], st_mesh *tile, int i_v)
{
    float value;
    
    char * letter;
    letter = strtok ( line, " " );
    if(letter == NULL)
    {
        return -1;
    }
    int i;

    for(i = 0; i < 6; i ++)
    {
        letter = strtok( NULL, " " );
        if(letter == NULL)
        {
            return -1;
        }
        value = atof(letter);
        tile->vert_pos[i_v] = value;
        i_v ++;
    }
    return i_v;
}

int parse_face(char line[], st_mesh *tile, int i_f)
{
    int value;
    int i, y;

    char *letter;
    letter = strtok( line, " ");

    for(y = 0; y < 3; y ++)
    {

        letter = strtok(NULL, " ");
        
        if(letter == NULL)
        {
            return -1;
        }
        value = atoi(letter);
        tile->face_pos[i_f] = value - 1;
        i_f ++;

        
    }
    return i_f;
}