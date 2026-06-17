#include "../../../include/src_include/Shared_tools/Load_tools/load_obj_format.h"

void load_file(char *path, st_tile *tile)
{
    /* Variables pour la gestion du fichier */
    FILE *file;
    struct stat sb;
    char line[50];

    /* Variables pour la gestion du regex*/
    const char *vert_reegex_def = "^v [-0-9]+.[0-9]* [-0-9]+.[0-9]* [-0-9]+.[0-9]*";
    const char *face_reegex_def = "^f( ([0-9]{0,3}/)[0-9]{0,3}/[0-9]{0,3}){4}";
    regex_t reegex;

    int match;

    /* Listes chainées */
    st_int_list *face_list;
    st_float_list *vert_list;

    init_int_lst(&face_list);
    init_float_lst(&vert_list);

    st_primitives_list *primitives_list;
    primitives_list = malloc(sizeof(st_primitives_list));

    primitives_list->float_list = vert_list;
    primitives_list->int_list = face_list;

    void (*parse_func)(char line[], st_tile *tile, st_primitives_list *primitives_list);

    /* Variables pour la gestion des erreurs */
    int err;
    int valid;
    char *text_err;
    size_t size_text_err;

    /* */
    tile->nb_vert = 0;
    tile->nb_face = 0;

    /* Valeur tampon */
    char previous = ' ';
    
    // ouverture du document + gestion des erreurs
    file = fopen(path, "r");

    if (stat(path, &sb) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Si la lecture n'a pas été mené à bien
    if (file == NULL)
    {
        err = errno;
        printf("fopen à échoué : ");

        if (err == EACCES)
        {
            printf("Le programe n'a pas les permission pour ouvrir le fichier.\n");
        }
        else if (err == ENOENT)
        {
            printf("Le programe n'a pas trouvé le fichier demandé.\n");
            printf("Chemin parcourus %s.\n", path);
        }
    }
    else
    {
        do
        {
            // Ici l'on va lire les ligne individuellement
            err = 0;
            valid = true;

            fgets(line, sb.st_size, file);
            if (ferror(file))
            {
                printf("Erreur lors de la lecture du document\n");
            }
            else
            {  
                // On vérifie la première lettre de la ligne, si c'est un v, on analyse pour les vetrex
                // Si c'est un f, on regarde avec les face
                if(line[0] == 'v' && previous != 'v')
                {
                    // Initialisation du regex
                    previous = 'v';
                    err = regcomp(&reegex, vert_reegex_def, REG_NOSUB | REG_EXTENDED);
                    parse_func = parse_vertext;
                    
                }
                else if(line[0] == 'f' && previous != 'f')
                {
                    // Initialisation du regex
                    previous = 'f';
                    err = regcomp(&reegex, face_reegex_def, REG_NOSUB | REG_EXTENDED);
                    parse_func = parse_face;
                }
                else if (line[0] != 'f' && line[0] != 'v')
                {
                    valid = false;
                }

                if (err == 0 && valid == true)
                {
                    // à présent on va voir s'il correspond à quelque chose dans les lignes
                    match = regexec (&reegex, line, 0, NULL, 0);

                    if(match == 0)
                    {
                        //printf("La ligne est bien reconnu comme coordonnée pour un obj 3D.\n");
                        parse_func(line, tile, primitives_list);
                        
                    }
                    else if(match == REG_NOMATCH)
                    {
                        //fprintf (stderr, "Cette ligne n'est pas reconnu comme ligne valide, elle est donc ignorée.\n");
                    }
                    else
                    {
                        // Ici gestion des erreur de regex
                        size_text_err = regerror(err, &reegex, NULL, 0);

                        // Ici le malloc fonction ainsi : l'on prend la taille d'un caractère (char) et on le multiplie par la taille :
                        // On peux aussi l'écrire sous cette forme : malloc(sizeof(char) * size_text_err)
                        text_err = malloc( sizeof(*text_err) * size_text_err);
                        
                        if(text_err)
                        {
                            regerror (err, &reegex, text_err, size_text_err);
                            fprintf (stderr, "%s\n", text_err);
                        }
                    }
                    
                }

            }

        } while (!feof(file));
        
        regfree(&reegex);
    }

    //print_float_list(vert_list);
    //print_int_list(face_list);

    // On attribue ici les valeurs qui ont été récuperer par le parse dans l'obj
    tile->nb_face = get_int_list_size(face_list);
    tile->nb_vert = get_float_list_size(vert_list);

    tile->face_pos = malloc(sizeof(int) * tile->nb_face);
    tile->vert_pos = malloc(sizeof(float) * tile->nb_vert);

    int i;

    for(i = 0; i < tile->nb_face; i ++)
    {
        tile->face_pos[i] = get_int_lst(face_list, i);
    }
    
    for(i = 0; i < tile->nb_vert; i ++)
    {
        tile->vert_pos[i] = get_float_lst(vert_list, i);
    }

    // On nettoie les infos qui ne nous servirons plus
    free(vert_list);
    free(face_list);
    free(primitives_list);

}


void parse_vertext(char line[], st_tile *tile, st_primitives_list *primitives_list)
{
    float value;
    
    char * letter;
    letter = strtok ( line, " " );
    
    int i;

    for(i = 0; i < 3; i ++)
    {
        letter = strtok( NULL, " " );
        value = atof(letter);
        put_float_lst(primitives_list->float_list, value);
    }
    
}

void parse_face(char line[], st_tile *tile, st_primitives_list *primitives_list)
{
    int value;
    int i, y;

    char *letter;

    letter = strtok( line, " ");

    for(y = 0; y < 4; y ++)
    {

        letter = strtok(NULL, "/");

        value = atoi(letter);
        put_int_lst(primitives_list->int_list, value);
        printf("%d\n", value);

        letter = strtok(NULL, "/");
        letter = strtok(NULL, "/");
        
        letter = strtok(NULL, " ");

        value = atoi(letter);
        printf("%d\n", value);
        put_int_lst(primitives_list->int_list, value);
    }
}