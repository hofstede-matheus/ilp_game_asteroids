#include "ilpgame.h"

#include "asteroid.h"
#include "quadTree.h"


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>





// How many frames time values to keep
// The higher the value the smoother the result is...
// Don't make it 0 or less :)
#define FRAME_VALUES 10

// An array to store frame times:
Uint32 frametimes[FRAME_VALUES];

// Last calculated SDL_GetTicks
Uint32 frametimelast;

// total frames rendered
Uint32 framecount;

// the value you want
float framespersecond;

SDL_Event event;





SDL_Surface *img;
SDL_Rect rectangle;
SDL_Rect rectangle2;

Uint32 clearColor;
SDL_Rect screenRect;

QuadTree *tree;
AsteroidList* list;

int asteroids_num = 2; //DAFAULT
int i = 0;
int lastInserted;

int x, y;

int move1 = 1;

int start_flag = 1;

Asteroid* asteroids[5];



// achei na internet pra medir os FPS
void fpsinit() {

        // Set all frame times to 0ms.
        memset(frametimes, 0, sizeof(frametimes));
        framecount = 0;
        framespersecond = 0;
        frametimelast = SDL_GetTicks();

}

void fpsthink() {

        Uint32 frametimesindex;
        Uint32 getticks;
        Uint32 count;
        Uint32 i;

        // frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
        // This value rotates back to 0 after it hits FRAME_VALUES.
        frametimesindex = framecount % FRAME_VALUES;

        // store the current time
        getticks = SDL_GetTicks();

        // save the frame time value
        frametimes[frametimesindex] = getticks - frametimelast;

        // save the last frame time for the next fpsthink
        frametimelast = getticks;

        // increment the frame count
        framecount++;

        // Work out the current framerate

        // The code below could be moved into another function if you don't need the value every frame.

        // I've included a test to see if the whole array has been written to or not. This will stop
        // strange values on the first few (FRAME_VALUES) frames.
        if (framecount < FRAME_VALUES) {

                count = framecount;

        } else {

                count = FRAME_VALUES;

        }

        // add up all the values and divide to get the average frame time.
        framespersecond = 0;
        for (i = 0; i < count; i++) {

                framespersecond += frametimes[i];

        }

        framespersecond /= count;

        // now to make it an actual frames per second value...
        framespersecond = 1000.f / framespersecond;

}










void draw_rect(QuadTree* quadTree){
    rectangle.x = quadTree->boundary.x;
    rectangle.y = quadTree->boundary.y;
    rectangle.w = quadTree->boundary.w;
    rectangle.h = quadTree->boundary.h;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rectangle);
    if(quadTree->type == 2){
        draw_rect(quadTree->nw);
        draw_rect(quadTree->ne);
        draw_rect(quadTree->sw);
        draw_rect(quadTree->se);
    }
    
}

void draw_circle_render(Asteroid* asteroid){
    int w, h;
    switch(asteroid->color){
        case 0:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            break;
        case 1:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            break;
        case 2:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            break;
        case 3:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            break;
        case 4:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            break;
    }
    for (w = 0; w < asteroid->radius * 2; w++)
    {
        for (h = 0; h < asteroid->radius * 2; h++)
        {
            int dx = asteroid->radius - w; // horizontal offset
            int dy = asteroid->radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (asteroid->radius * asteroid->radius))
            {
                SDL_RenderDrawPoint(renderer, asteroid->posX + dx, asteroid->posY + dy);
            }
        }
    }
}



void draw_circle(QuadTree* quadTree)
{
    Asteroid* asteroid = quadTree->asteroid;
    //printf("%d:%d\n", asteroid->posX, asteroid->posY);
    //Asteroid* asteroid2 = quadTree->asteroid2;

    if(quadTree->type == 1) draw_circle_render(asteroid);
    //if(!(asteroid2 == NULL)) draw_circle_render(asteroid2);

    if(quadTree->type == 2){
        draw_circle(quadTree->nw);
        draw_circle(quadTree->ne);
        draw_circle(quadTree->sw);
        draw_circle(quadTree->se);
    }
}



void init() {
    printf("!!");

    // pinta a tela de branco
    screenRect.x = screenRect.y = 0;
    screenRect.w = screen->w;
    screenRect.h = screen->h;
    clearColor = SDL_MapRGB(screen->format, 255, 255, 255);

    tRectangle rec = createRetangle(0, 0, 800, 600);
    printf("!%d",getSector(rec, createAsteroidAtPosition(700, 700, 10)));

    tree = createTree(0, 0, 800, 600);
    
    //rectangle2.x = 10;
    //rectangle2.y = 10;
    //rectangle2.w = 100;
    //rectangle2.h = 100;
    

    

    list = initList(); 

    /*
    for(i = 0; i < asteroids_num; i++){
        insertInList(list, createAsteroid());
        //printf("00\n");
    }
    */
    insertInList(list, createAsteroidAtPosition(210, 40, 10));
    insertInList(list, createAsteroidAtPosition(250, 60, 10));

    insertInList(list, createAsteroidAtPosition(742, 266, 10));
    insertInList(list, createAsteroidAtPosition(629, 218, 10));

    insertInList(list, createAsteroidAtPosition(311, 228, 10));
    insertInList(list, createAsteroidAtPosition(292, 78, 10));
    insertInList(list, createAsteroidAtPosition(485, 543, 10));

    insertInList(list, createAsteroidAtPosition(550, 140, 10));
    insertInList(list, createAsteroidAtPosition(150, 350, 10));
    insertInList(list, createAsteroidAtPosition(450, 370, 10));
    insertInList(list, createAsteroidAtPosition(70, 400, 10));

    
    Node* node = list->start;
    //printf("%d!\n", i);
    while(node != NULL){
        printf("%d:%d\n", node->asteroid->posX, node->asteroid->posY);    
        insertInQuadTree(tree, node->asteroid);
        //sleep(1);
        node = node->next;      
    }
    

    
    

  img = loadImage("walking1.png");

  
  i = 0;
  
    
}

void destroy() {
  SDL_FreeSurface(img);
}

void processEvent(SDL_Event event) {
  if (isQuitEvent(event)){
    endGameLoop();
  }
  switch(event.type){
      case SDL_KEYDOWN:
        if(move1){
            move1 = false;
        }else{
            move1 = true;
        }
        break;
  }
}

void update() {

    if(start_flag){
        
    }
    




    // mede o FPS
    //fpsthink();
    //printf("%f\n", framespersecond);




    
    /* calcula as colisões
    Node* node = list->start;
    while(node != NULL){
        Asteroid current = *node->asteroid;
        
        node->asteroid->color = 3;

        tCircle range = createCircle(node->asteroid->posX, node->asteroid->posY, node->asteroid->radius * 2);
        AsteroidList* asteroids = initList();
        query(asteroids, tree, range);
        Node* asteroidsAUX = asteroids->start;
        while(asteroidsAUX != NULL){
            Asteroid near = *asteroidsAUX->asteroid;
            // let d = dist(p.x, p.y, other.x, other.y);
            //              x1   y1   x2       y2
            // p = current
            // near = other
            if( !(current.posX == near.posX &&  current.posY == near.posY && current.radius == near.radius)){
                //printf("%d:%d     %d:%d \n", current.posX ,current.posY, near.posX, near.posY);
                //printf("%p    %p \n", &current, &near);
                float d = sqrt( pow (near.posX - current.posX, 2) + pow (near.posY - current.posY, 2));
                if(d < current.radius + near.radius){
                    node->asteroid->color = 4;
                    //printf("%f:%d\n", d, current.radius / 2 + near.radius / 2);
                } 

                
            }
            




            asteroidsAUX = asteroidsAUX->next;
        }
            





        node = node->next;      
    }
    


    */



    
    // move os asteroides
    //if(move1)
    //moveAsteroids(list, 0, 800, 0, 600);

    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            /* Look for a keypress */
            case SDL_KEYDOWN:
            move1 = false;
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        
                        break;
                    case SDLK_RIGHT:
                        move1 = false;
                        break;
                    case SDLK_UP:
                        move1 = false;
                        break;
                    case SDLK_DOWN:
                        move1 = false;
                        break;
                    default:
                        break;
                }
            
        }
    }
    /*
    // atualiza arvore

    tree = createTree(0, 0, 800, 600, 2);
    
    if(list->start != NULL){
        Node* node = list->start;
        //printf("%d!\n", i);
        while(node != NULL){
            //printf("%d:%d\n", node->asteroid->posX, node->asteroid->posY);    
            insertInQuadTree(tree, node->asteroid);
            node = node->next;      
        }
    }
    // e removendo
    // as coisas se movendo
    */
}

void draw() {
    //SDL_FillRect(screen, &screenRect, clearColor);
    //SDL_Flip(screen);
  
  
  //drawImage(img, asteroids[i]->posX, asteroids[i]->posY);
  /*
  Node* node = list->start;
  while(node != NULL){
    //printf("%d:%d\n", node->asteroid->posX, node->asteroid->posY);    
    drawImage(img, node->asteroid->posX, node->asteroid->posY);
    node = node->next;      
  }
  */
  
  //drawImage(img, 0, 0);

  draw_rect(tree);
  draw_circle(tree);

  //SDL_RenderDrawRect(renderer, &rectangle2);
  //clearTree(tree);
  
}

int main(int argc, char *argv[]) {
  srand(time(NULL)); 

  // se apenas tem um parametro (já que o argv[0] é o nome do programa)...
  if(argc == 2){
    char a = *argv[1];
    asteroids_num = atoi(argv[1]);
  }
  initSDL(800, 600);
  fpsinit();

  gameLoop();
  return 0;
}
