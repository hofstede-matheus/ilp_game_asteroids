#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "quadTree.h"

#define MAX_CAPACITY 2





// ***********************************************
// ******                                   ******
// ***********************************************

int contains(QuadTree* quadTree, int x, int y){
    int quadX = quadTree->boundary.x;
    int quadY = quadTree->boundary.y;
    int quadW = quadTree->boundary.w;
    int quadH = quadTree->boundary.h;
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

    return tree;
}
void insertInQuadTree(QuadTree* quadTree, Asteroid* asteroid){
    //checa se vai colocar no lugar certo
    if(!contains(quadTree, asteroid->posX, asteroid->posY))return;

    if(quadTree->size < quadTree->capacity){
        quadTree->asteroid[quadTree->size++] = asteroid;
    }else{
        // subdividir
        if(!quadTree->divided){
        quadTree->nw = createTree(quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->ne = createTree(quadTree->boundary.x + quadTree->boundary.w/2, quadTree->boundary.y, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->sw = createTree(quadTree->boundary.x , quadTree->boundary.y + quadTree->boundary.h/2, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->se = createTree(quadTree->boundary.x + quadTree->boundary.w/2, quadTree->boundary.y + quadTree->boundary.h/2, quadTree->boundary.w/2, quadTree->boundary.h/2, MAX_CAPACITY);
        quadTree->divided = 1;
        }
        insertInQuadTree(quadTree, asteroid);
    }
}



