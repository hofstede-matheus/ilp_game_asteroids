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
    asteroid->radius = (rand() % 15) + 10;
    asteroid->posX = rand() % 800;
    asteroid->posY = rand() % 600;
    

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
    

    asteroid->velX = ((rand() % 3) + 1) * sinal(); // 3 e 1
    asteroid->velY = ((rand() % 3) + 1) * sinal();
    asteroid->color = rand() % 3;     
	return asteroid;
}
Asteroid* createProjectiel(int x, int y, int x2, int y2){
    Asteroid* asteroid = (Asteroid*) malloc(sizeof(Asteroid));

    asteroid->radius = 5;
    asteroid->posX = x;
    asteroid->posY = y;


    // caso esteja apontado norte
    if(x == x2 && y < y2){
        asteroid->velX = 0;
        asteroid->velY = -3;
    }
    // caso esteja apontado ne
    if(x > x2 && y < y2){
        asteroid->velX = 3;
        asteroid->velY = -3;
    }
    // caso esteja apontado este
    if(x > x2 && y == y2){
        asteroid->velX = 3;
        asteroid->velY = 0;
    }
    // caso esteja apontado se
    if(x > x2 && y > y2){
        asteroid->velX = 3;
        asteroid->velY = 3;
    }
    // caso esteja apontado s
    if(x == x2 && y > y2){
        asteroid->velX = 0;
        asteroid->velY = 3;
    }
    // caso esteja apontado sw
    if(x < x2 && y > y2){
        asteroid->velX = -3;
        asteroid->velY = 3;
    }
    // caso esteja apontado west
    if(x < x2 && y == y2){
        asteroid->velX = -3;
        asteroid->velY = 0;
    }
    // caso esteja apontado nw
    if(x < x2 && y < y2){
        asteroid->velX = -3;
        asteroid->velY = -3;
    }


    asteroid->color = 1;



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


