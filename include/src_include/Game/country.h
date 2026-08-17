#ifndef COUNTRY
#define COUNTRY

/**
 * En gros, ce que j'aimerai faire comme ça,
 * C'est charger la map, pouvoir crée un tableau 2D côté CPU de
 * la carte et un côté GPU. Ainsi le côté GPU est simplement envoyé
 * à la Carte graphique (carte la carte en elle même ne change jamais)
 * et garder le côté CPU pour savoir si un bâtiment ajouter est sur une case
 * valide.
 * 
 * Je suis encore un peu pommé sur l'ensemble ici, je verrais ça plus tard.
 */
typedef struct st_tile_triangle
{
    
}st_tile;


int load_country(const char *path);
int create_country();
int delte_country();
#endif