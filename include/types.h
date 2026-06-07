#ifndef TYPE
#define TYPE

#include <stdbool.h>
#include <stdatomic.h>

//#include <GLFW/glfw3.h>

// Les chaine
typedef char t_letter;

typedef struct
{
    int length;
    int max_length;
    t_letter l;
    t_letter *next; 
}st_string;

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
    atomic_bool running;
    st_input input;
}st_engine;


// Structure pour la taille et le frame rate du contexte OpenGL
typedef struct {
    int size_x;
    int size_y;
    float frame_rate;
}st_loaded_windows_data;


typedef struct state
{
    void (*state)();

    void (*input_context)();
    void (*update_logic_context)();
    void (*update_render_context)();
    
    struct state *upper;
}state;

typedef struct {
    state *current_state;
}stack;


#endif