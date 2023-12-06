#include "sdl2-light.h"

#ifndef valeur_h
#define valeur_h

/*espace pour les constantes*/

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480


/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 32


/**
 * \brief Taille du missile
*/

#define MISSILE_SIZE 8

/**
 * \brief Vitesse verticale des vaisseaux ennemis
*/

#define ENEMY_SPEED 1

/**
 * \brief Vitesse verticale du missile
*/

#define MISSILE_SPEED 10

/**
 * \brief Nombre d'itérations de la boucle de jeu à la fin de la partie
*/

#define ITERATION 100

 /**
 * \brief Nombre d'ennemi
 */
#define NB_ENEMIES 5

/**
 * \brief Nombre d'ennemi
 */
#define VERTICAL_DIST 2*SHIP_SIZE

/**
 * @brief Taille des astéroïdes
 * 
 */
#define ASTEROIDE_SIZE 32

/**
 * @brief Vitesse des astéroïdes
 * 
 */
#define ASTEROIDE_SPEED 2

#endif

