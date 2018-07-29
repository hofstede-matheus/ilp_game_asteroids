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
    //isso é um circulo
    asteroid->radius = (rand() % 15) + 5;
    asteroid->posX = rand() % 800;
    asteroid->posY = rand() % 600;
    // posso subistituir por isso:

    asteroid->velX = ((rand() % 3) + 1) * sinal(); // 3 e 1
    asteroid->velY = ((rand() % 3) + 1) * sinal();
    asteroid->color = rand() % 3;     
	return asteroid;
}

Asteroid* createAsteroidAtPosition(int x, int y, int r) {
    // pra testes
    
    Asteroid* asteroid = (Asteroid*) malloc(sizeof(Asteroid));
    //isso é um circulo
    asteroid->radius = r;
    asteroid->posX = x;
    asteroid->posY = y;
    // posso subistituir por isso:

    asteroid->velX = ((rand() % 3) + 1) * sinal(); // 3 e 1
    asteroid->velY = ((rand() % 3) + 1) * sinal();
    asteroid->color = rand() % 3;     
	return asteroid;
}
int sinal(){
    int negativo = rand() % 2;
    if(negativo){
        negativo = -1;
    }else{
        negativo = 1;
    }
    return negativo;
}


