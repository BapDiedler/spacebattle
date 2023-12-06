/**
 * \file logique.c
 * \brief Fonctions sur la partie logique de Spacebattle
 * \author Baptiste DIEDLER & Marc LICHTNER
 * \version 1.0
 * \date 111 Mai 2022
 */

#include "sdl2-light.h"
#include "sdl2-ttf-light.h"
#include "constantes.h"
#include "logique.h"
#include "graphique.h"
#include <math.h>




/*ESPACE INITIALISATION DES DONNEES*/


/**
 * @brief La fonction initialise les données du sprite
 * @param sprite Le sprite qui sera initialisé
 * @param x La position x
 * @param y la position y
 * @param w la largeur
 * @param h la hauteur
 * @param v la vitesse verticale
 */
void init_sprite(sprite_t* sprite,int x, int y, int w, int h, int v){
    sprite->x = x;
    sprite->y = y;
    sprite->w = w;
    sprite->h = h;
    sprite->v = v;
    set_visible(sprite);//le sprite est visible au début de la partie
}
/**
 * @brief Initialise les données des ennemies
 * @param world les données du monde
 */
void init_ennemies(world_t* world){
    int i;
    for (i=0;i<NB_ENEMIES;i++)
    {
        world->enemies[i] = malloc(sizeof(sprite_t));
        init_sprite(world->enemies[i],rand()%(SCREEN_WIDTH - SHIP_SIZE/2 - SHIP_SIZE/2) + SHIP_SIZE/2,- SHIP_SIZE/2 - i * VERTICAL_DIST,SHIP_SIZE,SHIP_SIZE,ENEMY_SPEED);//placement semi aleatoire des ennemis
        ennemy_out(world->enemies[i],world);
    }
}

/**
 * @brief Rend invisible les ennemies, les missiles et les asteroides si le jeu est fini
 * @param world les données du monde
 */
void invisible_ennemies(world_t* world){
    if (is_game_over(world))
    {
        set_invisible(world->asteroide);
        set_invisible(world->missile);
        for (int i=0;i<NB_ENEMIES;i++)
            set_invisible(world->enemies[i]);
    }
}

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */

void init_data(world_t * world){
    world->cpt=0;
    //le jeu n'est pas en pause
    world->pause=0;
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    //initialisation du champ score
    world->score=0;
    //Initialisation du compteur d'ennemies sorti
    world->enemies_out = 0;
    // Initialisation du vaisseau
    world->vaisseau = malloc(sizeof(sprite_t));
    init_sprite(world->vaisseau,(SCREEN_WIDTH - SHIP_SIZE)/2,SCREEN_HEIGHT-2*SHIP_SIZE,SHIP_SIZE,SHIP_SIZE,0);
    // Initialisation des ennemies
    init_ennemies(world);
    // Initialisation des astéroïdes
    world->asteroide = malloc(sizeof(sprite_t));
    init_sprite(world->asteroide,rand()%(SCREEN_WIDTH - SHIP_SIZE/2 - SHIP_SIZE/2) + SHIP_SIZE/2,- ASTEROIDE_SIZE,ASTEROIDE_SIZE,ASTEROIDE_SIZE,ASTEROIDE_SPEED);
    // Initialisation du missile
    world->missile = malloc(sizeof(sprite_t));
    init_sprite(world->missile,world->vaisseau->x + SHIP_SIZE/2 - MISSILE_SIZE/2,world->vaisseau->y - SHIP_SIZE/2 + MISSILE_SIZE/2,MISSILE_SIZE,MISSILE_SIZE,0);
    world->missile = set_invisible(world->missile);
}




/*ESPACE DE CHANGEMENT DES DONNEES*/


/**
 * @brief Met à jour les données sur les ennemies
 * @param world données du monde
 */
void update_enemies(world_t* world){
    int i;
    for (i=0;i<NB_ENEMIES;i++){
        world->enemies[i]->y += world->enemies[i]->v;//déplacement de l'ennemi
        ennemy_out(world->enemies[i],world);//si l'ennemi sort
        handle_sprites_collision(world->vaisseau,world->enemies[i]);//collision avec le missile
        handle_sprites_collision(world->missile,world->enemies[i]);//collision avec le vaisseau
    }
}

/**
 * @brief Met à jour les données sur l'astéroïde
 * @param world données du monde
 */
void update_asteroides(world_t* world){
    world->asteroide->y += world->asteroide->v;//déplacement de l'asteroide
    asteroide_out(world->asteroide);//si l'adsteroide sort
    handle_sprites_collision(world->vaisseau,world->asteroide);//collision entre le vaisseau et l'asteriode
}

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t * world){
    if(world->pause==0){
        world->missile->y -= world->missile->v;
        //espace pour les limites du vaisseau
        left_border(world->vaisseau);
        right_border(world->vaisseau);
        down_border(world->vaisseau);
        top_border(world->vaisseau);
        //espace pour l'update des asteroides
        update_asteroides(world);
        handle_missile_asteroide_collision(world->missile,world->asteroide);
        //espace pour les limites du missile
        missile_out(world->missile);
        //si les ennemies sont éliminés
        for(int i=0;i<NB_ENEMIES;++i){
            if(sprites_collide(world->missile,world->enemies[i])){
                world->score++;
            }
        }
        update_enemies(world);
        compute_game(world);
        invisible_ennemies(world);
        //boucle pour la fin du jeu
        if(world->gameover==1){
            world->cpt++;
        }  
    }
}

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche ctrl gauche est appuyée
            if (event->key.keysym.sym == SDLK_RCTRL || event->key.keysym.sym == SDLK_LCTRL){
                //le jeu est en pause
                world->pause=1-world->pause;
            }
            //si la touche appuyée est 'Echap'
            if (event->key.keysym.sym == SDLK_ESCAPE){
                //On indique la fin du jeu
                world->gameover = 1;
            }
            //si le jeu est en pause on ne peut pas jouer
            if(world->pause==0){
                //si la touche appuyée est 'D'
                if(event->key.keysym.sym == SDLK_d){
                    printf("La touche D est appuyée\n");
                }
                //si la touche appuyée est 'Flèche du bas'
                if (event->key.keysym.sym == SDLK_DOWN){
                    //on bouge le vaisseau vers le bas
                    world->vaisseau->y +=10;
                    world->missile->y +=10;
                }
                //si la touche appuyée est 'Flèche du haut'
                if (event->key.keysym.sym == SDLK_UP){
                    //on bouge le vaisseau vers le bas
                    world->vaisseau->y -=10;
                    world->missile->y -=10;
                }
                //si la touche appuyée est 'Flèche de gauche'
                if (event->key.keysym.sym == SDLK_LEFT){
                    //On bouge le vaisseau vers la gauche
                    world->vaisseau->x -= 10;
                    world->missile->x -= 10;
                }
                //si la touche appuyée est 'Flèche de droite'
                if (event->key.keysym.sym == SDLK_RIGHT){
                    //On bouge le vaisseau vers la gauche
                    world->vaisseau->x += 10;
                    world->missile->x += 10;
                }
                //si la touche appuyée est 'Espace'
                if (event->key.keysym.sym == SDLK_SPACE){
                    if (world->vaisseau->is_visible == 0 && world->missile->is_visible==1) // Vérifie que le vaisseau soit visible pour qu'il puisse tirer
                    {
                    //On fait apparaître le missile
                    world->missile->x = world->vaisseau->x + SHIP_SIZE/2 - MISSILE_SIZE/2;
                    world->missile->y = world->vaisseau->y - SHIP_SIZE/2 + MISSILE_SIZE/2;
                    set_visible(world->missile);
                    world->missile->v = MISSILE_SPEED;
                    }
                }
            }
        }
    }
}

/**
 * @brief Rend le sprite visible
 * @param sprite le sprite
 * @return sprite_t* 
 */
sprite_t* set_visible(sprite_t* sprite){
    sprite->is_visible = 0;//modificztion du champ is_visible
    return sprite;
}

/**
 * @brief Rend le sprite invisible
 * @param sprite le sprite
 * @return sprite_t* 
 */
sprite_t* set_invisible(sprite_t* sprite){
    sprite->is_visible = 1;//modificztion du champ is_visible
    return sprite;
}




/*ESPACE EN CAS DE COLLISION*/


/**
 * @brief fonction qui fait disparaître le missile si il est en collision avec l'astéroïde
 * @param missile le missile
 * @param asteroide l'astéroïde
 */
void handle_missile_asteroide_collision(sprite_t* missile, sprite_t* asteroide)
{
    if(missile->is_visible == 0 && asteroide->is_visible == 0 && sprites_collide(missile,asteroide) == 1)
    {
        // vitesse nulle
        missile->v=0;
        // disparition du missile
        set_invisible(missile);
    }
}

/**
 * @brief Vérifie si le vaisseau commence à dépasser la limite inférieur et si oui, le replace
 * @param vaisseau le vaisseau
 */
sprite_t* down_border(sprite_t * vaisseau){
    if (vaisseau->y+SHIP_SIZE >= SCREEN_HEIGHT)
        vaisseau->y = SCREEN_HEIGHT-SHIP_SIZE;//replacement du vaisseau sur la limite du bas
    return vaisseau;
}

/**
 * @brief Vérifie si le vaisseau commence à dépasser la limite supérieur et si oui, le replace
 * @param vaisseau le vaisseau
 */
sprite_t* top_border(sprite_t * vaisseau){
    if (vaisseau->y <= 0)
        vaisseau->y = 0;//replacement du vaisseau sur la limite du haut
    return vaisseau;
}

/**
 * @brief Vérifie si le vaisseau commence à dépasser la limite gauche et si oui, le replace
 * @param vaisseau le vaisseau
 */
sprite_t* left_border(sprite_t * vaisseau){
    if (vaisseau->x <= 0)
        vaisseau->x = 0;//replacement du vaisseau sur la limite gauche
    return vaisseau;
}

/**
 * @brief Vérifie si le vaisseau commence à dépasser la limite droite et si oui, le replace
 * @param vaisseau le vaisseau
 */
sprite_t* right_border(sprite_t * vaisseau){
    if (vaisseau->x + SHIP_SIZE >= SCREEN_WIDTH)
        vaisseau->x = SCREEN_WIDTH - SHIP_SIZE;//replacement du vaisseau sur la limite droite
    return vaisseau;
}

/**
 * @brief Fonction qui vérifie si l'ennemi a dépassé l'écran et incrémente aussi le nombre d'ennemies sortis
 * 
 * @param ennemi l'ennemi
 * @param world données du monde
 * @return l'ennemi
 */
sprite_t* ennemy_out(sprite_t* ennemi,world_t* world){
    if (ennemi->y > SCREEN_HEIGHT + SHIP_SIZE/2 && ennemi->is_visible==0){
        ennemi->v=0;//vitesse nulle
        set_invisible(ennemi);//disparition de l'ennemy de la fenetre
        world->enemies_out++;//mise à jour du conteur d'ennemis sortie du jeu
        return ennemi;
    }
}

/**
 * @brief Fonction qui vérifie si le missile sors de l'écran
 * 
 * @param missile le missile
 * @return sprite_t* le missile
 */
sprite_t* missile_out(sprite_t* missile){
    if (missile->y < 0 - MISSILE_SIZE/2)
        missile=set_invisible(missile);//disparition du missile
    return missile;
}

/**
 * @brief Fonction qui vérifie si l'astéroïde a dépassé l'écran et si oui, le replace
 * 
 */
sprite_t* asteroide_out(sprite_t* asteroide){
    if (asteroide->y > SCREEN_HEIGHT)
    {
        asteroide->x = rand()%(SCREEN_WIDTH - SHIP_SIZE/2 - SHIP_SIZE/2) + SHIP_SIZE/2;//placement semi aleatoir des asteroides
        asteroide->y = -ASTEROIDE_SIZE;
    }
    return asteroide; 
}

/**
 * @brief Vérifie si deux sprites sont en collision
 * 
 * @param sp2 le sprite 2
 * @param sp1 le sprite 1
 * @return int 1 si il y a collision, 0 sinon
 */
int sprites_collide(sprite_t* sp2,sprite_t* sp1){
    int centre_x_sp1 = sp1->x + SHIP_SIZE, centre_y_sp1 = sp1->y + SHIP_SIZE, centre_x_sp2 = sp2->x + SHIP_SIZE, centre_y_sp2 = sp2->y + SHIP_SIZE, rayon_sp1=2*pow(sp1->w/2,2), rayon_sp2=2*pow(sp2->w/2,2);
    if (sqrt(pow(centre_x_sp1-centre_x_sp2,2)+pow(centre_y_sp1-centre_y_sp2,2))<= sqrt(rayon_sp1+rayon_sp2) && sp1->is_visible==0 && sp2->is_visible==0)//vérification de la distance
        return 1;
    else
        return 0;
}

/**
*@brief fonction qui passe la vitesse à 0 si les sprites sont en collisions et les rends invisibles
*@param sprite1 premier sprite
*@param sprite2 second sprite
*/
void handle_sprites_collision(sprite_t* sprite1, sprite_t* sprite2){
    if(sprite1->is_visible == 0 && sprite2->is_visible == 0 && sprites_collide(sprite1,sprite2) == 1){
        //vitesse nulle
        sprite1->v=0;
        sprite2->v=0;
        //disparition des sprites
        set_invisible(sprite1);
        set_invisible(sprite2);
    }
}




/*FIN DE LA PARTIE ( NETTOYAGE DES DONNÉES/RÈGLE DU JEU )*/


/**
 * \brief La fonction s'occupe des règles du jeu
 * \param world les données du monde
 */
 void compute_game(world_t *world){
     //Si le vaisseau est détruit
     if(world->vaisseau->is_visible!=0){
         world->gameover=1;
         world->score=0;
     }
     //Si le vaisseau n'est pas détruit
     else if(world->vaisseau->is_visible==0){
         //Si tous les ennemies ont été éliminés
         if(world->score==NB_ENEMIES){
             world->gameover=1;
         }
         //Si le joueur a survécu mais il n'a pas éliminé tous les ennemis
         else if(world->enemies_out+world->score==NB_ENEMIES){
             world->gameover=1;
         }
     }
 }

 /**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t * world){
    return world->gameover;
}

/**
* \brief la fonction dit si l'attente final est passée
* \param world les données du monde
*/
int THE_END(world_t * world){
    if(world->cpt == ITERATION){//si le temps d'attente à la fin du jeu est passé
        return 1;
    }
    else
        return 0;
}

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->vaisseau);
    free(world->asteroide);
    free(world->missile);
    for (int i=0;i<NB_ENEMIES;i++)
    {
        free(world->enemies[i]);
    }
}