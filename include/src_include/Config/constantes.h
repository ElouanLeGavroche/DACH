#ifndef CONSTANTES
#define CONSTANTES

#define DONE 0
#define ERROR -1
#define SUCCES 1
#define FAILED_MALLOC 2
#define NULL_POINTER 3


#define PATH_FISEL_MAP "ressources/maps/fisel.json"

// Path vers fichiers
#define PATH_LOAD_GAME_DATA "data/configuration.json"


/** Format des fichiers data **/
// Window Info
#define SCREEN_WITH_DEFAULT 1024
#define SCREEN_HEIGHT_DEFAULT 768
#define SCREEN_FRAME_RATE_DEFAUL 60
#define DEFAULT_RATIO 3.0/4.0

#define TIME_PER_FRAME 1.0 / SCREEN_FRAME_RATE_DEFAUL
#define ENGINE_SPEED 60
#define TIME_PER_TICK 1.0 / ENGINE_SPEED

#endif 