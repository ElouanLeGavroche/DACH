#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "../../../include/src_include/Shared_tools/Load_tools/load_image.h"


st_image load_texture(const char *path, int width, int height, int nr_channels)
{
    st_image image;
 
    image.path = path;
    image.width = width;
    image.height = height;
    image.nr_channels = nr_channels;

    image.data = stbi_load(image.path, &image.width, &image.height, &image.nr_channels, 0);

    if(image.data == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture de l'image\n");
    }

    return image;
}