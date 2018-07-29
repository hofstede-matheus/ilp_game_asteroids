
#include "circle.h"
#include "asteroidList.h"




typedef struct tQuadTree{ 
    tRectangle boundary;
    int type; // 0 = região vazia; 1 = ponto; 2 = arvore;
    //int divided;
    Asteroid* asteroid;
    // usa apenas se for região;
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
void clearTree(QuadTree* quadTree);
int getSector(tRectangle boundary, Asteroid* asteroid);



    
