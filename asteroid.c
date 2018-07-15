#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "asteroid.h"

// ***********************************************
// ******                                   ******
// ***********************************************

Asteroid* createAsteroid() {
    Asteroid* asteroid = (Asteroid*) malloc(sizeof(Asteroid));
    asteroid->radius = (rand() % 50) + 10;
    asteroid->posX = rand() % 500;
    asteroid->posY = rand() % 500;
    asteroid->vel = (rand() % 5) + 1;
    asteroid->color = rand() % 3;     
	return asteroid;
}
