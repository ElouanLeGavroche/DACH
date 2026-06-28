#ifndef LOAD_IMAGE
#define LOAD_IMAGE

#include <stdio.h>

#include "../../../../extern_lib/stb_image/stb_image.h"

#include "../../../types.h"

st_image load_texture(const char *path, int width, int height, int nr_channels);


#endif