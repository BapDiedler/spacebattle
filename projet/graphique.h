#ifndef graphique_h
#define graphique_h

#include "sdl2-light.h"
#include "constantes.h"



/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct ressources_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* vaisseau; /*!< Texture liée au vaisseau. */
    SDL_Texture* ennemi; /*!< Texture liée aux ennemies. */
    SDL_Texture* asteroide; /*!< Texture liée aux astéroïdes. */
    SDL_Texture* missile; /*!< Texture liée au missile. */
    TTF_Font* font; /*< Police pour l'affichage.*/
};

/**
 * \brief Type qui correspond aux textures du jeu
*/
typedef struct ressources_s ressources_t;


/**
 * \brief La fonction nettoie les textures
 * \param ressources les ressources
*/
void clean_textures(ressources_t *ressources);

/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param ressources les ressources du jeu
*/
void  init_ressources(SDL_Renderer *renderer, ressources_t *ressources);

/**
 * @brief La fonction applique texture associée au sprite
 * @param renderer le renderer
 * @param textures la texture du sprite
 * @param sprite le sprite
 */
void apply_sprite(SDL_Renderer* renderer,SDL_Texture* texture, sprite_t* sprite);

/**
 * @brief applique la texture associée aux ennemies
 * @param renderer le renderer
 * @param texture la texture du sprite
 * @param world les données du mondes contenant le tableau d'ennemies
 */
void apply_enemies(SDL_Renderer* renderer,SDL_Texture* texture, world_t * world);

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/
void apply_background(SDL_Renderer *renderer, ressources_t *textures);

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *ressources);

/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param ressources les ressources
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *ressources, world_t * world);

/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param ressources les ressources
 * \param wordl le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *ressources, world_t * world);

#endif