/**
 * \file tests.c
 * \brief Programme de test des fonctions de Spacebattle
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
 * @brief Teste si la vitesse s'annule en cas de collision
 * @param sp2 sprite 2
 * @param sp1 sprite 1
 */
void test_handle_sprites_collision_param(sprite_t* sp1, sprite_t* sp2){
    print_sprite(sp1);
    print_sprite(sp2);
    handle_sprites_collision(sp1,sp2);
    print_sprite(sp1);
    print_sprite(sp2);
}

/**
 * @brief fait appel à la fonction handle_sprites_collision
 */
void test_handle_sprites_collision(){
    sprite_t * sp1 = malloc(sizeof(size_t)), * sp2 = malloc(sizeof(size_t));
    init_sprite(sp1,0,0,0,0,10);
    init_sprite(sp2,0,0,0,0,15);
    test_handle_sprites_collision_param(sp1,sp2);
}

/**
 * @brief Teste si les sprites sont en collisions
 * @param sp2 sprite 2
 * @param sp1 sprite 1
 */
void test_sprites_collide_param(sprite_t* sp2, sprite_t* sp1){
    if (sprites_collide(sp2,sp1)==1)
        printf("Les sprites sont en collisions.\n");
    else
        printf("Les sprites ne sont pas en collisions.\n");
}

/**
 * @brief Fait appel à la fonction test_sprites
 * 
 */
void test_sprites_collide(){
    sprite_t * sp2 = malloc(sizeof(sprite_t)), * sp1 = malloc(sizeof(sprite_t));
    init_sprite(sp2,0,0,SHIP_SIZE,SHIP_SIZE,0);
    init_sprite(sp2,1,10,SHIP_SIZE,SHIP_SIZE,0);
    test_sprites_collide_param(sp2,sp1);
    init_sprite(sp2,0,0,SHIP_SIZE,SHIP_SIZE,0);
    init_sprite(sp2,600,100,SHIP_SIZE,SHIP_SIZE,0);
    test_sprites_collide_param(sp2,sp1);
}

/**
 * @brief Teste la fonction border left
 * @param vaisseau le vaisseau
 */
void test_left_border_param(sprite_t * vaisseau){
    print_sprite(vaisseau);
    left_border(vaisseau);
    print_sprite(vaisseau);
}

/**
 * @brief Fait appel à la fonction border left
 */
void test_left_border(){
    sprite_t * vaisseau = malloc(sizeof(sprite_t));
    init_sprite(vaisseau,-10,0,0,0,0);
    test_left_border_param(vaisseau);
    init_sprite(vaisseau,10,0,0,0,0);
    test_left_border_param(vaisseau);
}

/**
 * @brief Teste la fonction border right
 * @param vaisseau le vaisseau
 */
void test_right_border_param(sprite_t * vaisseau){
    print_sprite(vaisseau);
    right_border(vaisseau);
    print_sprite(vaisseau);
}

/**
 * @brief Fait appel à la fonction border right
 */
void test_right_border(){
    sprite_t * vaisseau = malloc(sizeof(sprite_t));
    init_sprite(vaisseau,1000,0,0,0,0);
    test_right_border_param(vaisseau);
    init_sprite(vaisseau,10,0,0,0,0);
    test_right_border_param(vaisseau);
}

/**
 * @brief Fonction qui initialise et affiche les valeurs du sprite
 * 
 * @param sprite le sprite
 * @param x sa position horizontale
 * @param y sa position verticale
 * @param w sa largeur
 * @param h sa hauteur
 * @param v sa vitesse
 */
void test_init_sprite_param(sprite_t* sprite,int x, int y, int w, int h, int v, world_t* world){
    init_sprite(sprite, x, y, w, h, v);
    print_sprite(sprite);
    out_of_screen(sprite, world);
}


/**
 * @brief Fonction qui appelle la fonction de test init_sprite avec différentes valeurs
 * 
 */
void test_init_sprite(){
    world_t* world;
    sprite_t* test = malloc(sizeof(sprite_t));
    test_init_sprite_param(test,90,20,30,4,50,world);
    test_init_sprite_param(test,20,0,323,42,220,world);
    test_init_sprite_param(test,88,200,343,400,60,world);
    test_init_sprite_param(test,10,840,31,30,0,world);
}

/**
 * @brief Fonction qui test l'initialisation des ennemies
 * 
 */
void test_init_ennemies(){
    world_t* world = malloc(sizeof(world_t));
    init_ennemies(world);
    for (int i = 0;i<NB_ENEMIES;i++)
    {
        print_sprite(world->enemies[i]);
    }
}

/**
 * @brief Affiche les valeurs du sprite
 * @param sprite le sprite
 */
void print_sprite(sprite_t* sprite){
    printf("La pos x est %d,  la pos y est %d. La hauteur est %d et la largeur est %d. La vitesse est %d.\n", sprite->x,sprite->y,sprite->h,sprite->w,sprite->v);
}

int main(int argc, char * argv[]){
    //test_init_sprite();
    //test_sprites_collide();
    //test_left_border();
    //test_right_border();
    //test_handle_sprites_collision();
    test_init_ennemies();
    return EXIT_SUCCESS;
}
