#ifndef TYPE
#define TYPE

//Chaine de caractère pour récuperer les éléments de windows info
typedef char t_window_info[4];

// Structure pour la taille et le frame rate du contexte OpenGL
typedef struct {
    int size_x;
    int size_y;
    float frame_rate;
}t_loaded_windows_data;

#endif