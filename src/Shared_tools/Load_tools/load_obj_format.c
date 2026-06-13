#include "../../../include/src_include/Shared_tools/Load_tools/load_obj_format.h"

float load_file(char *path){
    FILE *file;
    char line[30];
    /**
     * Au vu de mes observations, les fichiers obj sont constituer de ligne faisant maximum
     * 31 caractères. Ma solution est alors d'avoir une string de 30 (31 octet), et faire
     * par-dessus un travail de parse.
    */
    
    file = fopen(path, "r");
    
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
        }
    }
    else
    {
        while(!feof(file))
        {
            fgets(line, 30, file);
            parse_line(line);
            
            if (ferror( file ))
            {
                printf("Erreur lors de la lecture du document\n");
            }
            else
            {
                printf("%s\n", line);
            }
        }
        fclose(file);
    }
    free(file);

    return 0;
}

void parse_line(char file[])
{

}