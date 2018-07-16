#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "asteroid.h"



// ***********************************************
// ******                                   ******
// ***********************************************

Asteroid* createAsteroid() {
    // armengue pra a velocidade ser negativa tb;
    int negativo = rand() % 2;
    if(negativo){
        negativo = -1;
    }else{
        negativo = 1;
    }
    Asteroid* asteroid = (Asteroid*) malloc(sizeof(Asteroid));
    asteroid->radius = (rand() % 20) + 5;
    asteroid->posX = rand() % 800;
    asteroid->posY = rand() % 600;
    asteroid->vel = ((rand() % 5) + 1) * negativo;
    asteroid->color = rand() % 3;     
	return asteroid;
}



