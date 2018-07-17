#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "quadTree.h"

#define MAX_CAPACITY 2






// ***********************************************
// ******                                   ******
// ***********************************************

/*
1. Se C1C2 == R1 + R2
     A e B se tocam.
2. Se C1C2 > R1 + R2
     A e B não se tocam.
3. Se C1C2 < R1 + R2
      A e B se intersectam.
*/

int circleIntersection(Asteroid asteroid1, Asteroid asteroid2){
    int distSq = (asteroid1.posX - asteroid2.posX) * (asteroid1.posX - asteroid2.posX) +
                 (asteroid1.posY - asteroid2.posY) * (asteroid1.posY - asteroid2.posY);
    int radSumSq = (asteroid1.radius + asteroid2.radius) * (asteroid1.radius + asteroid2.radius);
    if (distSq == radSumSq)
        return 1;
    else if (distSq > radSumSq)
        return -1;
    else
        return 0;
}



int contains(tRectangle boundary, int x, int y){
    int quadX = boundary.x;
    int quadY = boundary.y;
    int quadW = boundary.w;
    int quadH = boundary.h;
    if(x > quadX - quadW && x < quadX + quadW && y > quadY - quadH && y < quadY + quadH){
        return 1;
    }
    else{
        return 0;
    }
}

QuadTree* createTree(int x, int y, int w, int h, int capacity){
    QuadTree* tree = (QuadTree*) malloc(sizeof(QuadTree));
    tree->boundary.x = x;
    tree->boundary.y = y;
    tree->boundary.w = w;
    tree->boundary.h = h;

    tree->capacity = MAX_CAPACITY;
    tree->size = 0;
    tree->divided = 0;

    tree->asteroid1 = NULL;
    tree->asteroid2 = NULL;

    
    

    return tree;
}
void insertInQuadTree(QuadTree* quadTree, Asteroid* asteroid){
    //checa se vai colocar na região do quadrado certo
    if(!contains(quadTree->boundary, asteroid->posX, asteroid->posY))return;
    /*
    if(quadTree->size < quadTree->capacity){
        quadTree->asteroid[quadTree->size++] = asteroid;
    }*/
    if(quadTree->size == 0){
        quadTree->asteroid1 = asteroid;
        quadTree->size++;
    }else if(quadTree->size == 1){
        quadTree->asteroid2 = asteroid;
        quadTree->size++;
    }
    else{
        // subdividir
        if(!quadTree->divided){
        quadTree->nw = createTree(quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->ne = createTree(quadTree->boundary.x + quadTree->boundary.w/2, quadTree->boundary.y, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->sw = createTree(quadTree->boundary.x , quadTree->boundary.y + quadTree->boundary.h/2, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->se = createTree(quadTree->boundary.x + quadTree->boundary.w/2, quadTree->boundary.y + quadTree->boundary.h/2, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->divided = 1;
        }
        //insertInQuadTree(quadTree, asteroid);
        insertInQuadTree(quadTree->nw, asteroid);
        insertInQuadTree(quadTree->ne, asteroid);
        insertInQuadTree(quadTree->sw, asteroid);
        insertInQuadTree(quadTree->se, asteroid);

    }
}
// pra inicialmente não haver colisões
void initialInsertInQuadTree(QuadTree* quadTree, Asteroid* asteroid){
    //checa se vai colocar no lugar certo
    if(!contains(quadTree->boundary, asteroid->posX, asteroid->posY))return;
    /*
    if(quadTree->size < quadTree->capacity){
        quadTree->asteroid[quadTree->size++] = asteroid;
    }*/
    if(quadTree->size == 0){
        quadTree->asteroid1 = asteroid;
        quadTree->size++;
    }else if(quadTree->size == 1){
        quadTree->asteroid2 = asteroid;
        quadTree->size++;
    }
    else{
        // subdividir
        if(!quadTree->divided){
        quadTree->nw = createTree(quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->ne = createTree(quadTree->boundary.x + quadTree->boundary.w/2, quadTree->boundary.y, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->sw = createTree(quadTree->boundary.x , quadTree->boundary.y + quadTree->boundary.h/2, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->se = createTree(quadTree->boundary.x + quadTree->boundary.w/2, quadTree->boundary.y + quadTree->boundary.h/2, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->divided = 1;
        }
        //insertInQuadTree(quadTree, asteroid);
        insertInQuadTree(quadTree->nw, asteroid);
        insertInQuadTree(quadTree->ne, asteroid);
        insertInQuadTree(quadTree->sw, asteroid);
        insertInQuadTree(quadTree->se, asteroid);

    }
}
void query(AsteroidList* asteroidList, QuadTree* quadTree, tCircle range){
    if(asteroidList == NULL) asteroidList = initList();

    if(!intersectsCircle(quadTree->boundary, range)){
        return;
    }
    if(quadTree->asteroid1 != NULL)
    if(containsPoint(range, quadTree->asteroid1->posX, quadTree->asteroid1->posY)) insertInList(asteroidList, quadTree->asteroid1);
    if(quadTree->asteroid2 != NULL)
    if(containsPoint(range, quadTree->asteroid2->posX, quadTree->asteroid2->posY)) insertInList(asteroidList, quadTree->asteroid2);

    if(quadTree->divided){
        query(asteroidList, quadTree->nw, range);
        query(asteroidList, quadTree->ne, range);
        query(asteroidList, quadTree->sw, range);
        query(asteroidList, quadTree->se, range);

        
    }

    /*
    intersects()
    if(quadTree->boundary )
    */
}





