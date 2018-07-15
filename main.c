#include "ilpgame.h"
#include "asteroid.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>



//preocupado


SDL_Surface *img;
int asteroids_num = 1; //DAFAULT
int i;


Asteroid* asteroids[5];

void init() {

  img = loadImage("carro.png");

  
  for(i = 0; i < asteroids_num; i++){
    asteroids[i] = createAsteroid();
  }
  
}

void destroy() {
  SDL_FreeSurface(img);
}

void processEvent(SDL_Event event) {
  if (isQuitEvent(event))
    endGameLoop();
}

void update() {
}

void draw() {
  
  for(i = 0; i < asteroids_num; i++)
  {
  drawImage(img, asteroids[i]->posX, asteroids[i]->posY);
  }  
  drawImage(img, 100, 100);
}

int main(int argc, char *argv[]) {
  srand(time(NULL)); 

  // se apenas tem um parametro (já que o argv[0] é o nome do programa)...
  if(argc == 2){
    char a = *argv[1];
    asteroids_num = atoi(argv[1]);
  }
  initSDL();
  gameLoop();
  return 0;
}
