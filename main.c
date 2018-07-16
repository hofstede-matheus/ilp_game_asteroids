#include "ilpgame.h"

#include "asteroid.h"
#include "quadTree.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>



//preocupado


SDL_Surface *img;
SDL_Rect rectangle;
SDL_Rect rectangle2;

Uint32 clearColor;
SDL_Rect screenRect;

QuadTree *tree;

int asteroids_num = 1; //DAFAULT
int i;


Asteroid* asteroids[5];


void draw_rect(QuadTree* quadTree){
    rectangle.x = quadTree->boundary.x;
    rectangle.y = quadTree->boundary.y;
    rectangle.w = quadTree->boundary.w;
    rectangle.h = quadTree->boundary.h;
    SDL_RenderDrawRect(renderer, &rectangle);
    if(quadTree->divided){
        draw_rect(quadTree->nw);
        draw_rect(quadTree->ne);
        draw_rect(quadTree->sw);
        draw_rect(quadTree->se);
    }
    
}


void draw_circle(Asteroid asteroid)
{
    int w, h;
    switch(asteroid.color){
        case 0:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            break;
        case 1:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            break;
        case 2:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            break;
    }
    for (w = 0; w < asteroid.radius * 2; w++)
    {
        for (h = 0; h < asteroid.radius * 2; h++)
        {
            int dx = asteroid.radius - w; // horizontal offset
            int dy = asteroid.radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (asteroid.radius * asteroid.radius))
            {
                SDL_RenderDrawPoint(renderer, asteroid.posX + dx, asteroid.posY + dy);
            }
        }
    }
}




void init() {


    screenRect.x = screenRect.y = 0;
    screenRect.w = screen->w;
    screenRect.h = screen->h;
    clearColor = SDL_MapRGB(screen->format, 255, 255, 255);

    
    

  img = loadImage("carro.png");

  tree = createTree(0, 0, 800, 600, 2);

    rectangle2.x = 10;
    rectangle2.y = 10;
    rectangle2.w = 100;
    rectangle2.h = 100;

  
  for(i = 0; i < asteroids_num; i++){
    insertInQuadTree(tree, createAsteroid());
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
    SDL_FillRect(screen, &screenRect, clearColor);
    //SDL_Flip(screen);
  
  
  for(i = 0; i < asteroids_num; i++)
  {
  //drawImage(img, asteroids[i]->posX, asteroids[i]->posY);
  //draw_circle(*asteroids[i]);
  }  
  drawImage(img, 0, 0);

  draw_rect(tree);
  SDL_RenderDrawRect(renderer, &rectangle2);
  
}

int main(int argc, char *argv[]) {
  srand(time(NULL)); 

  // se apenas tem um parametro (já que o argv[0] é o nome do programa)...
  if(argc == 2){
    char a = *argv[1];
    asteroids_num = atoi(argv[1]);
  }
  initSDL(800, 600);
  gameLoop();
  return 0;
}
