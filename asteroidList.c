#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "asteroidList.h"


Node* createNode(int index, Asteroid* asteroid){
    Node* node = (Node*) malloc(sizeof(Node));
    node->index = index;
    node->asteroid = asteroid;
    node->next = NULL;
    node->previous = NULL;

}

AsteroidList* initList(){
    AsteroidList* lista = (AsteroidList*) malloc(sizeof(AsteroidList));
    lista->start = NULL;
    lista->end = NULL;
    lista->numElem = 0;
    return lista;
}
void insertInList(AsteroidList* asteroidList, Asteroid* asteroid){
    // caso lista esteja vazia

    if(asteroidList->numElem == 0){
        Node* node = createNode(asteroidList->numElem, asteroid);
        asteroidList->start = node;
        asteroidList->end = node;
        asteroidList->numElem++;
        
    }else{
        Node* node = createNode(asteroidList->numElem, asteroid);
        node->previous = asteroidList->end;
        asteroidList->end->next = node;
        asteroidList->end = node;
        asteroidList->numElem++;
    }

}
void removeByIndex(AsteroidList* asteroidList, int i){
    if(i == 0){
        Node* node = asteroidList->start;
        Node* next = node->next;
        next->previous = NULL;
        asteroidList->start = next;
        free(node);

    }else if(i == asteroidList->numElem - 1){
        Node* node = asteroidList->end;
        Node* previous = node->previous;
        previous->next = NULL;
        asteroidList->end = previous;
        free(node);
    }else{
        Node* node = asteroidList->start;
        while(node->index != i){
            node = node->next;
        }
        Node* previous = node->previous;
        Node* next = node->next;

        previous->next = next;
        next->previous = previous;

        free(node);

        asteroidList->numElem--;

    }
}
void removeAtEnd(AsteroidList* asteroidList){
    if(asteroidList->numElem == 1){
        Node* node = asteroidList->end;
        asteroidList->start = NULL;
        asteroidList->end = NULL;
        free(node);


    }else{
        Node* node = asteroidList->end;
        Node* anterior = node->previous;
        anterior->next = NULL;
        asteroidList->end = anterior;
        free(node);
    }
    asteroidList->numElem--;
}

void moveAsteroids(AsteroidList* asteroidList, int x0, int x1, int y0, int y1){
    Node* node = asteroidList->start;
    while(node != NULL){
        node->asteroid->posX += node->asteroid->velX;
        node->asteroid->posY += node->asteroid->velY;
        if(node->asteroid->posX < x0) node->asteroid->velX *= -1;
        if(node->asteroid->posX > x1) node->asteroid->velX *= -1;
        if(node->asteroid->posY < y0) node->asteroid->velY *= -1;
        if(node->asteroid->posY > y1) node->asteroid->velY *= -1;
        node = node->next;      
    }
}

