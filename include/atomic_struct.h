#ifndef ATOMIC_STRUCT
#define ATOMIC_STRUCT

#include <stdbool.h>
#include <stdatomic.h>


// Les chaine
typedef char letter;

typedef struct
{
    int length;
    int max_length;
    letter l;
    letter *next; 
}string;

// Le bool "one of them" sert à verifier s'il y en a
// au moins un d'actionner. Pour éviter de parcourir
// un switch pour rien.
typedef struct
{
    bool escape;
    bool one_of_them;
}st_input;

typedef struct
{
    char actual_canva;
    atomic_bool running;
    st_input input;
}st_engine;

/*
Ceci est un essaie de structure pour hierachiser les pages
*/

typedef struct
{
    int id;
}st_frame;

typedef st_frame frame_list;

typedef struct
{
    st_frame main_frame;
    frame_list sub_frame;    
}st_full_frame;

#endif