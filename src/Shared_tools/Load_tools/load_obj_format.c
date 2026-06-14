#include "../../../include/src_include/Shared_tools/Load_tools/load_obj_format.h"

float load_file(char *path)
{
    //
    FILE *file;
    struct stat sb;
    char line[LINE_SIZE];
    //
    //const char *reegex_def = "v [-0-9]+.[0-9]* [-0-9]+.[0-9]* [-0-9]+.[0-9]*";
    const char *reegex_def = "v 1";
    regex_t reegex;
    int match;
    float x, y, z;
    //
    int err;
    char *text_err;
    size_t size_text_err;

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
        // Technique un peu barbare pour ignoré les deux première ligne
        fgets(line, sb.st_size, file);
        fgets(line, sb.st_size, file);

        do
        {
            // Ici l'on va lire les ligne individuellement
            err = 0;
            fgets(line, sb.st_size, file);

            if (ferror(file))
            {
                printf("Erreur lors de la lecture du document\n");
            }
            else
            {  
                // Initialisation du regex
                err = regcomp(&reegex, reegex_def, REG_NOSUB | REG_EXTENDED);
                if (err == 0)
                {
                    // à présent on va voir s'il correspond à quelque chose dans les lignes
                    match = regexec (&reegex, reegex_def, 0, NULL, 0);
                    printf("match : %d\nreg_val : %s \nline : %s\n", match, line, reegex_def);
                    if(match == 0)
                    {
                        printf("La ligne est bien reconnu comme coordonnée pour un obj 3D.\n");
                    }
                    else if(match == REG_NOMATCH)
                    {
                        fprintf (stderr, "Cette ligne n'est pas reconnu comme ligne valide, elle est donc ignorée.\n");
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
                else
                {
                    printf("erreur lors de la création du regex\n");
                }
            }

        } while (!feof(file));
        fclose(file);
    }

    return 0;
}
