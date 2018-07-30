#include "spaceship.h"
#include <stdlib.h>

Spaceship* createSpaceship(){
    Spaceship* spaceship = (Spaceship*) malloc(sizeof(Spaceship));
    spaceship->x = 400;
    spaceship->y = 300;
    spaceship->vel = 0.0f;
    spaceship->angle = PI / 4;

}

// void querySpaceshipCollision(AsteroidList** asteroidList, QuadTree* quadTree, int x, int y){

// }

// void handleSpaceshipMoviment(const Uint8 *keyboard, Spaceship *spaceship){
    
// }