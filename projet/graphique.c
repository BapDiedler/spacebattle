/**
 * \file graphique.c
 * \brief Fonctions sur la partie graphique de Spacebattle
 * \author Baptiste DIEDLER & Marc LICHTNER
 * \version 1.0
 * \date 18 mars 2022
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "constantes.h"
#include "logique.h"
#include "graphique.h"

/**
 * \brief La fonction nettoie les textures
 * \param ressources les ressources
*/

void clean_textures(ressources_t *ressources){
    clean_texture(ressources->background);
    clean_texture(ressources->vaisseau);
    clean_texture(ressources->ennemi);
    clean_texture(ressources->asteroide);
    clean_texture(ressources->missile);
    clean_font(ressources->font);
}



/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param ressources les ressources du jeu
*/

void  init_ressources(SDL_Renderer *renderer, ressources_t *ressources){
    ressources->background = load_image( "ressources/space-background.bmp",renderer);
    ressources->vaisseau = load_image("ressources/spaceship1.bmp",renderer);
    ressources->ennemi = load_image("ressources/ennemyfinal.bmp",renderer);
    ressources->asteroide = load_image("ressources/asteroide1.bmp",renderer);
    ressources->missile = load_image("ressources/missile2.bmp",renderer);
    ressources->font = load_font("ressources/arial.ttf",14);   
}

/**
 * @brief La fonction applique texture associée au sprite
 * @param renderer le renderer
 * @param ressources la texture du sprite
 * @param sprite le sprite
 */
void apply_sprite(SDL_Renderer* renderer,SDL_Texture* texture, sprite_t* sprite){
    if (sprite->is_visible == 0){//si pas visible le sprite ne s'affiche pas
        if(texture != NULL){
            apply_texture(texture, renderer, sprite->x, sprite->y);
        }
    }
}

/**
 * @brief applique la texture associée aux ennemies
 * @param renderer le renderer
 * @param texture la texture du sprite
 * @param world les données du mondes contenant le tableau d'ennemies
 */
void apply_enemies(SDL_Renderer* renderer,SDL_Texture* texture, world_t * world){
    for (int i=0;i<NB_ENEMIES;i++)
    {
        apply_sprite(renderer,texture,world->enemies[i]);
    }
}

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/
void apply_background(SDL_Renderer *renderer, ressources_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param ressources les ressources
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,ressources_t *ressources){
    
    //on vide le renderer
    clear_renderer(renderer);
    //application des textures dans le renderer
    apply_background(renderer, ressources);//texture du background
    apply_sprite(renderer,ressources->vaisseau,world->vaisseau);//texture du vaisseau
    apply_sprite(renderer,ressources->asteroide,world->asteroide);//etxture des asteroides
    apply_sprite(renderer,ressources->missile,world->missile);//texture des missiles
    apply_enemies(renderer,ressources->ennemi,world);//etxture des enemies
    // on applique le texte
    char message[100];
    sprintf(message,"Score:%i",world->score);//affichage du score du joueur
    apply_text(renderer,10,10,70,40,message,ressources->font);//position du messsage sur l'écran
    if(world->vaisseau->is_visible!=0) //Si le vaisseau est détruit
        apply_text(renderer,60,200,200,40,"Game Over",ressources->font);//message si la partie est perdue
    else if (world->score < NB_ENEMIES && world->gameover == 1)
        apply_text(renderer,60,200,200,40,"You stayed alive",ressources->font);//message si le joueur est resté en vie
    else if (world->score == NB_ENEMIES && world->gameover == 1)
        apply_text(renderer,60,200,200,40,"You won",ressources->font);//message si tous les ennemies sont eliminés
    // on met à jour l'écran
    update_screen(renderer);
}



/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param ressources les ressources
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, ressources_t *ressources, world_t * world){
    clean_data(world);//nettoyage des données du monde
    clean_textures(ressources);//nettoyage des ressources
    clean_sdl(renderer,window);//effacement de la fenetre
}



/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param ressources les ressources
 * \param wordl le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, ressources_t *ressources, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);//initialisation de la fenetre de départ
    init_ttf();
    init_data(world);//initialisation des données du monde
    init_ressources(*renderer,ressources);//initialisation des ressources
}