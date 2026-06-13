#include "../../../include/src_include/Shared_tools/Load_tools/load_obj_format.h"

float load_file(char *path){
    FILE *file;
    
    struct stat sb;
    
    file = fopen(path, "r");
    
    if (stat(path, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char line[sb.st_size];
    
    // Technique un peu barbare pour ignoré les deux première ligne
    fgets(line, sb.st_size, file);
    fgets(line, sb.st_size, file);

    if (file == NULL)
    {
        int errsv = errno;
        printf("fopen à échoué : ");
        
        if(errsv == EACCES)
        {
            printf("Le programe n'a pas les permission pour ouvrir le fichier.\n");
        }
        else if(errsv == ENOENT)
        {
            printf("Le programe n'a pas trouvé le fichier demandé.\n");
            printf("Chemin parcourus %s.\n", path);
        }
    }
    else
    {
        while(!feof(file))
        {
            fgets(line, sb.st_size, file);
            printf("%s", line); 
            //parse_line(line);
            
            if (ferror( file ))
            {
                printf("Erreur lors de la lecture du document\n");
            }

        }
        fclose(file);
    }
    
    return 0;
}

