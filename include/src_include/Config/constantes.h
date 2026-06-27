#ifndef CONSTANTES
#define CONSTANTES

#define DONE 0
#define ERROR -1

// Path vers fichiers
#define PATH_LOAD_GAME_DATA "data/configuration.json"


/** Format des fichiers data **/
// Window Info
#define SCREEN_WITH_DEFAULT 1280
#define SCREEN_HEIGHT_DEFAULT 720
#define SCREEN_FRAME_RATE_DEFAUL 60

#define TIME_PER_FRAME 1.0 / SCREEN_FRAME_RATE_DEFAUL


#define X1_SPEED_LOGIC 40
#define X2_SPEED_LOGIC 40
#define X3_SPEED_LOGIC 60


#define TIME_PER_TICK 1.0 / X1_SPEED_LOGIC

#define EMPTY_LIST -1


#endif 