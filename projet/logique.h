#ifndef logique_h
#define logique_h

#include "sdl2-light.h"
#include "constantes.h"

/**
 * @brief Représentation du sprite
 */
struct sprite_s{
    int x; /*!< Correspondt à la position horizontale du sprite */
    int y; /*!< Correspondt à la position verticale du sprite */
    int w; /*!< Correspondt à la largeur du sprite */
    int h; /*!< Correspondt à la hauteur du sprite */
    int v; /*!< Correspondt à la vitesse verticale du sprite */
    int is_visible; /*!< Correspondt à la visibilité du sprite, 1 si il est vissible et 0 s'in ne l'est pas */
};

/**
 * \brief Type qui correspond aux sprites
 */

typedef struct sprite_s sprite_t;

struct world_s{
    sprite_t* vaisseau; /*!< Champ correspondant au vaisseau */
    //sprite_t* ennemi; /*!< Champ correspondant a l'ennemi 1 */
    sprite_t* missile; /*!< Champ correspondant au missile*/
    sprite_t* enemies[NB_ENEMIES]; /*!< Champ correspondant a un tableau de sprites d'ennemies*/
    sprite_t* asteroide;
    int enemies_out; /*< Champ correspondant au nombre d'ennemies sortie de l'écran*/
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    int score; /*!<Champ indiquant le score du joueur>!*/
    int cpt; /*<Champ pour le temps d'attente à la fin du jeu>*/
    int pause; /*<Champ pour savoir si le jeu est en pause>*/
};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;


/**
 * @brief Rend le sprite visible
 * @param sprite le sprite
 * @return sprite_t* 
 */
sprite_t* set_visible(sprite_t* sprite);

/**
 * @brief Rend le sprite invisible
 * @param sprite le sprite
 * @return sprite_t* 
 */
sprite_t* set_invisible(sprite_t* sprite);

/**
 * @brief La fonction initialise les données du sprite
 * @param sprite Le sprite qui sera initialisé
 * @param x La position x
 * @param y la position y
 * @param w la largeur
 * @param h la hauteur
 * @param v la vitesse verticale
 */
void init_sprite(sprite_t* sprite,int x, int y, int w, int h, int v);

/**
 * @brief Initialise les données des ennemies
 * @param world les données du monde
 */
void init_ennemies(world_t* world);

/**
*@brief fonction qui passe la vitesse à 0 si les sprites sont en collisions
*@param sprite1 premier sprite
*@param sprite2 second sprite
*/
void handle_sprites_collision(sprite_t* sprite1, sprite_t* sprite2);

/**
 * @brief fonction qui fait disparaître le missile si il est en collision avec l'astéroïde
 * @param missile le missile
 * @param asteroide l'astéroïde
 */
void handle_missile_asteroide_collision(sprite_t* missile, sprite_t* asteroide);

/**
 * @brief Vérifie si le vaisseau commence à dépasser la limite gauche et si oui, le replace
 * @param vaisseau le vaisseau
 */
sprite_t* left_border(sprite_t * vaisseau);

/**
 * @brief Vérifie si le vaisseau commence à dépasser la limite droite et si oui, le replace
 * @param vaisseau le vaisseau
 */
sprite_t* right_border(sprite_t * vaisseau);

/**
 * @brief Vérifie si le vaisseau commence à dépasser la limite du bas et si oui, le replace
 * @param vaisseau le vaisseau
 */
sprite_t* down_border(sprite_t * vaisseau);

/**
 * @brief Vérifie si le vaisseau commence à dépasser la limite du haut et si oui, le replace
 * @param vaisseau le vaisseau
 */
sprite_t* top_border(sprite_t * vaisseau);

/**
 * @brief Fonction qui vérifie si l'ennemi a dépassé l'écran et si oui, le replace
 * 
 * @param ennemi l'ennemi
 * @return l'ennemi
 */
sprite_t* ennemy_out(sprite_t* ennemi,world_t* world);

/**
 * @brief Fonction qui vérifie si le missile sors de l'écran
 * 
 * @param missile le missile
 * @return sprite_t* le missile
 */
sprite_t* missile_out(sprite_t* missile);

/**
 * @brief Fonction qui vérifie si l'astéroïde a dépassé l'écran et si oui, le replace
 * @param asteroide l'astéroïde
 * @return sprite_t* l'astéroïde
 */
sprite_t* asteroide_out(sprite_t* asteroide);

/**
 * @brief Vérifie si deux sprites sont en collision
 * 
 * @param sp2 le sprite 2
 * @param sp1 le sprite 1
 * @return int 1 si il y a collision, 0 sinon
 */
int sprites_collide(sprite_t* sp2,sprite_t* sp1);

/**
 * @brief Affiche les valeurs du sprite
 * @param sprite le sprite
 */
void print_sprite(sprite_t* sprite);

/**
 * @brief Rend invisible les ennemies, les missiles et les asteroides si le jeu est fini
 * @param world les données du monde
 */
void invisible_ennemies(world_t* world);

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world);

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world);

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world);

/**
* \brief la fonction dit si l'attente final est passée
* \param world les données du monde
*/
int THE_END(world_t * world);

/**
 * @brief Met à jour les données sur les ennemies
 * @param world données du monde
 */
void update_enemies(world_t* world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world);

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world);

/**
 * \brief La fonction s'occupe des règles du jeu
 * \param world les données du monde
 */
 void compute_game(world_t *world);

#endif