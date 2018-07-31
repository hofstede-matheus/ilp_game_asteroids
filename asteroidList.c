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
// procurar o projétil cuja posição é a dada e remove
// tem que remover pra não gastar toda memória, né
void removeByIndex(AsteroidList* asteroidList, int x, int y){
    Node* node = asteroidList->start;
    while(node != NULL){
        // se achou
        if(node->asteroid->posX == x && node->asteroid->posY == y){
            // se só tem um elemento
            if(asteroidList->numElem == 1){
                asteroidList->start = asteroidList->end = NULL;
                free(node);
            }else{
                // se node é início
                if(node->previous == NULL){
                    asteroidList->start = node->next;
                    asteroidList->start->previous = NULL;
                    free(node);
                } else if (node->next == NULL){
                    asteroidList->end = node->previous;
                    asteroidList->end->next = NULL;
                    free(node);
                }else{
                    node->previous->next = node->next;
                    node->next->previous = node->previous;
                    free(node);
                }
            }
            asteroidList->numElem--;
            //Node* out = node;
            break;
            
        }
        node = node->next;
    }

}
/*
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
*/

// move os asteroides na velocidade deles
void moveAsteroids(AsteroidList* asteroidList, int x0, int x1, int y0, int y1){
    Node* node = asteroidList->start;
    while(node != NULL){
        node->asteroid->posX += node->asteroid->velX;
        node->asteroid->posY += node->asteroid->velY;
        // caso saia da tela, inverte a velocidade
        if(node->asteroid->posX < x0) node->asteroid->velX *= -1;
        if(node->asteroid->posX > x1) node->asteroid->velX *= -1;
        if(node->asteroid->posY < y0) node->asteroid->velY *= -1;
        if(node->asteroid->posY > y1) node->asteroid->velY *= -1;
        node = node->next;      
    }
}
void moveProjectiel(AsteroidList* projectielList, int x0, int x1, int y0, int y1){
    Node* node = projectielList->start;
    while(node != NULL){
        node->asteroid->posX += node->asteroid->velX;
        node->asteroid->posY += node->asteroid->velY;
        // caso saia da tela, remove o asteroide
        if(node->asteroid->posX < x0) removeByIndex(projectielList, node->asteroid->posX, node->asteroid->posY);
        if(node->asteroid->posX > x1) removeByIndex(projectielList, node->asteroid->posX, node->asteroid->posY);;
        if(node->asteroid->posY < y0) removeByIndex(projectielList, node->asteroid->posX, node->asteroid->posY);;
        if(node->asteroid->posY > y1) removeByIndex(projectielList, node->asteroid->posX, node->asteroid->posY);;
        node = node->next;      
    }
}


