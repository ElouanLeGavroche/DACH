#include "../../../include/src_include/Shared_tools/Load_tools/load_map.h"

void load_map(const char *path)
{
    FILE *file = NULL;
    char *line = NULL;

    int ok = 0;
    size_t cap = 0;

    while (getline(&line, &cap, file) != -1)
    {
        printf("%s\n", line);
    }
}