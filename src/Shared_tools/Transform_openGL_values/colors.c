#include "../../../include/src_include/Shared_tools/Transform_openGL_values/colors.h"

int hexa_to_01(char val[1]){

}

float num_to_01(int val)
{
    float new_val;

    if(val > 255)
    {
        printf("valeur trop grande, je t'invite à te faire foutre\n");
        new_val = 0.0;
    }
    else if(val < 0)
    {
        printf("valeur trop petite, je t'invite à te faire foutre\n");
        new_val = 0.0;
    }
    else
    {
        new_val = val * 1.0 / 255;
    }

    return new_val;
}