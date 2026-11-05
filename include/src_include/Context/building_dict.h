#ifndef BUILDING_DICT
#define BUILDING_DICT

typedef enum{
    ROAD,
    NATURE,
    RIVER,
    
    HOUSE,
    CASTLE

}building_type;

typedef enum{
    DIRTY,
    ROCKY
}road_subtype;

typedef enum{
    WOOD,
    ROCK,
    FLOOR_FLOWER,
    SMALL_ROCK,
}nature_subtype;

typedef enum{
    LONG_ROCK_HOUSE,
}house_subtype;

#endif