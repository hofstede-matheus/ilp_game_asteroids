#include "asteroid.h"


// na verdade, na verdade isso é uma mistura de lista com fila, usei assim pra não precisar ficar rodando pela lista toda vez que for adicionar
// e não quero a restrição da fila de remover apenas do final

typedef struct node {
    int index;
    Asteroid* asteroid;
    struct node* next;
    struct node* previous;
} Node;

typedef struct { 
    Node* start;
    Node* end;
    int numElem;
} AsteroidList;

AsteroidList* initList();
void insertInList(AsteroidList* asteroidList, Asteroid* asteroid);
void removeByIndex(AsteroidList* asteroidList, int i);
void removeAtEnd(AsteroidList* asteroidList);
void moveAsteroids(AsteroidList* asteroidList, int x0, int x1, int y0, int y1);