#include "../../../include/src_include/Shared_tools/Load_tools/load_shader.h"

/**
 * @brief inspiré du code ce trouvant sur ce site : https://moderncprogramming.com/loading-a-glsl-shader-from-file-in-opengl-using-pure-c/
 */
char* load_shader(const char* file_name)
{
    /* Définition des variables */
    FILE *fp;
    long size = 0;
    char* shader_content;
    
    /* Première lectuire pour connaitre la taille du fichier */
    fp = fopen(file_name, "rb");
    if(fp == NULL) {

        fclose(fp);
        
        printf("échec de la lecture du shader, vérifiez le path\n");
        return NULL;
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp)+1;
    fclose(fp);

    /* Lire le contenu du fichier */
    fp = fopen(file_name, "r");
    if(fp == NULL)
    {
        fclose(fp);
        return NULL;
    }
    
    shader_content = memset(malloc(size), '\0', size);
    fread(shader_content, 1, size-1, fp);
    fclose(fp);

    return shader_content;

}