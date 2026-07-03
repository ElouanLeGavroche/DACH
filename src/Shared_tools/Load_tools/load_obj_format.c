#include "../../../include/src_include/Shared_tools/Load_tools/load_obj_format.h"

int load_file(char *path, st_mesh *tile)
{
    /* Variables pour la gestion du fichier */
    FILE *file = NULL;
    char *line = NULL;
    
    // Entier qui préviendra en cas d'erreur
    int ok = 0;

    size_t cap = 0;


    /* */
    tile->vertex_float_count = 0;
    tile->index_count = 0;
    
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
                            tile->vertex_float_count ++;
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
                            tile->index_count ++;
                        }
                        y ++;
                            
                    }
                }
                
            }
            fclose(file);
        }


        tile->face_indice = malloc(sizeof(int) * tile->index_count);
        if(tile->face_indice == NULL)
        {
            free(line);
            return -1;
        }
        else
        {
            tile->vert_pos = malloc(sizeof(float) * tile->vertex_float_count);
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

            while (getline(&line, &cap, file) != -1 && ok != ERROR)
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
                            if(i_v == ERROR)
                            {
                                ok = ERROR;
                            }
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
    return ok;
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
    int i = 0;
    char * letter;

    letter = strtok ( line, " " );
    if(letter == NULL)
    {
        return -1;
    }
    

    while(letter[i] != '\0' && letter[i] != '\n')
    {
        letter = strtok( NULL, " " );
        if(letter == NULL)
        {
            return -1;
        }
        value = atof(letter);
        tile->vert_pos[i_v] = value;
        i_v ++;
        
        i++;
    }
    // Diag de la ligne
    if(i != 9 && i != 8)
    {
        fprintf(stderr, "Attention, il n'y a %d élément dans la ligne du vert, comportement indéfini\n", i);
        fprintf(stderr, "autoriser : \nTriangles : 8 \nCarrés 9\n");
        fprintf(stderr, "Ce message s'adresse au développeur, merci de demander à Paotr Neñvel de te donner la programme qui permet de "
                        "passer du format .obj au .obj personnaliser du projet.\n");
        
        return ERROR;
    }
    return i_v;
}

int parse_face(char line[], st_mesh *tile, int i_f)
{
    int value;
    int i = 0;

    char *letter;
    letter = strtok( line, " ");

    //while(letter[i] != '\0' && letter[i] != '\n')
    for(i = 0; i < 3; i ++)
    {

        letter = strtok(NULL, " ");
        
        if(letter == NULL)
        {
            fprintf(stderr, "Erreur lors du strtok pour les indices des face.\n");
            return -1;
        }
        value = atoi(letter);
        tile->face_indice[i_f] = value - 1;
        i_f ++;        
        
    }

    if(i != 2 && i != 3)
    {
        fprintf(stderr, "Attention, il n'y a %d élément dans les indices des faces, comportement indéfini\n", i);
        fprintf(stderr, "autoriser : \nTriangles : 2 \nCarrés 3\n");
        fprintf(stderr, "Ce message s'adresse au développeur, merci de demander à Paotr Neñvel de te donner la programme qui permet de "
                        "passer du format .obj au .obj personnaliser du projet.\n");
        
        return ERROR;
    }
    return i_f;
}