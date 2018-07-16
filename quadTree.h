#include "rectangle.h"
#include "asteroid.h"



typedef struct tQuadTree{ 
    tRectangle boundary;
    int capacity;
    int size; // total de asteroides guardados
    Asteroid* asteroid[2];
    int divided;
    struct tQuadTree* nw;
    struct tQuadTree* ne;
    struct tQuadTree* sw;
    struct tQuadTree* se;
} QuadTree;


               
// ***********************************************
QuadTree* createTree(int x, int y, int w, int h, int capacity);
void insertInQuadTree(QuadTree* quadTree, Asteroid* asteroid);
//void clearTree( TreeNode** r);


    
