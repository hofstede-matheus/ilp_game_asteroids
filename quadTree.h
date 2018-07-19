
#include "circle.h"
#include "asteroidList.h"




typedef struct tQuadTree{ 
    tRectangle boundary;
    //int capacity;
    int size; // total de asteroides guardados
    Asteroid* asteroid;
    //Asteroid* asteroid2;
    int divided;
    struct tQuadTree* nw;
    struct tQuadTree* ne;
    struct tQuadTree* sw;
    struct tQuadTree* se;
} QuadTree;


               
// ***********************************************
QuadTree* createTree(int x, int y, int w, int h);
void insertInQuadTree(QuadTree* quadTree, Asteroid* asteroid);
//void clearTree( TreeNode** r);
void query(AsteroidList* asteroidList, QuadTree* quadTree, tCircle range);


    
