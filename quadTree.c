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

int getSector(tRectangle boundary, Asteroid* asteroid){
    // nw = 0, ne = 1, sw = 2, se = 3;
    // x e y
    if(asteroid->posX <= boundary.x + boundary.w / 2
    && asteroid->posY <= boundary.y + boundary.h / 2) return 0;

    if(asteroid->posX > boundary.x + boundary.w / 2
    && asteroid->posY <= boundary.y + boundary.h / 2) return 1;

    if(asteroid->posX <= boundary.x + boundary.w / 2
    && asteroid->posY > boundary.y + boundary.h / 2) return 2;

    if(asteroid->posX > boundary.x + boundary.w / 2
    && asteroid->posY > boundary.y + boundary.h / 2) return 3;


}

QuadTree* createTree(int x, int y, int w, int h){
    QuadTree* tree = (QuadTree*) malloc(sizeof(QuadTree));
    tree->boundary.x = x;
    tree->boundary.y = y;
    tree->boundary.w = w;
    tree->boundary.h = h;
    tree->type = 0;
    //tree->divided = 0;

    tree->nw = NULL;
    tree->ne = NULL;
    tree->sw = NULL;
    tree->se = NULL;

    printf("CREATE TREE: x=%d; y=%d w=%d h=%d \n", tree->boundary.x, tree->boundary.y, tree->boundary.w, tree->boundary.h);

    
    

    return tree;
}

void subdivide(QuadTree* quadTree, Asteroid* asteroid, Asteroid* vizinho){
    quadTree->nw = createTree(quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w/2, quadTree->boundary.h/2);
    quadTree->ne = createTree(quadTree->boundary.x + quadTree->boundary.w/2, quadTree->boundary.y, quadTree->boundary.w/2, quadTree->boundary.h/2);
    quadTree->sw = createTree(quadTree->boundary.x , quadTree->boundary.y + quadTree->boundary.h/2, quadTree->boundary.w/2, quadTree->boundary.h/2);
    quadTree->se = createTree(quadTree->boundary.x + quadTree->boundary.w/2, quadTree->boundary.y + quadTree->boundary.h/2, quadTree->boundary.w/2, quadTree->boundary.h/2);
    quadTree->type = 2;
    if(getSector(quadTree->boundary, asteroid) == getSector(quadTree->boundary, vizinho)){
        // recursivamente até achar um lugar que os dois não estão juntos
    printf("Vizinhos ainda estão juntos\n");
        switch(getSector(quadTree->boundary, asteroid)){
            case 0:
                printf("ambos são é NW\n");
                subdivide(quadTree->nw, asteroid, vizinho);
                break;
            case 1:
                printf("ambos são é NE\n");                
                subdivide(quadTree->ne, asteroid, vizinho);
                break;
            case 2:
                printf("ambos são é SW\n");
                subdivide(quadTree->sw, asteroid, vizinho);
                break;
            case 3:
                printf("ambos são é SE\n");
                subdivide(quadTree->se, asteroid, vizinho);
                break;
        }
    }else{
        // coloca o asteroide no lugar
    printf("vizinhos separados\n");
        switch(getSector(quadTree->boundary, asteroid)){
            case 0:
                printf("ast são é NW\n");
                insertInQuadTree(quadTree->nw, asteroid);
                break;
            case 1:
                printf("ast são é NE\n");        
                insertInQuadTree(quadTree->ne, asteroid);
                break;
            case 2:
                printf("ast são é SW\n");
                insertInQuadTree(quadTree->sw, asteroid);
                break;
            case 3:
                printf("ast são é SE\n");
                insertInQuadTree(quadTree->se, asteroid);
                break;
        }
        switch(getSector(quadTree->boundary, vizinho)){
            case 0:
                printf("viz são é NW\n");
                insertInQuadTree(quadTree->nw, vizinho);
                break;
            case 1:
                printf("viz são é NE\n");  
                insertInQuadTree(quadTree->ne, vizinho);
                break;
            case 2:
                printf("viz são é SW\n");
                insertInQuadTree(quadTree->sw, vizinho);
                break;
            case 3:
                printf("viz são é SE\n");
                insertInQuadTree(quadTree->se, vizinho);
                break;
        }
    }


}
void insertInQuadTree(QuadTree* quadTree, Asteroid* asteroid){
    /*
    if(!contains(quadTree->boundary, asteroid->posX, asteroid->posY)){
        printf("o asteroid %d:%d não pertence a região {x=%d; y=%d w=%d h=%d}\n", asteroid->posX, asteroid->posY, quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w, quadTree->boundary.h);
        return;
    }
    */

    printf("INSERT TREE CHAMADA\n");
    if(quadTree->type == 0){
        printf("Achou espaço\n");
        printf("ACHOU INSERT TREE asteroid %d:%d região {x=%d; y=%d w=%d h=%d} \n", asteroid->posX, asteroid->posY, quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w, quadTree->boundary.h);
        quadTree->asteroid = asteroid;
        quadTree->type = 1;
    }else if(quadTree->type == 1){
        // subdivide
        printf("quadtree precisou der dividida\n");
        printf("filhos {\n");      
        subdivide(quadTree, asteroid, quadTree->asteroid);
        printf("}\n");
        
        // pega o que vai adicionar e o vizinho e coloca pra baixo

        //dado o boundary
        // verifica se atual e vizinho estão no mesmo quadrado

    }else{

        printf("é uma arvore vê a posição e desce até achar um lugar vazio\n");
        switch(getSector(quadTree->boundary, asteroid)){
            case 0:
                printf("ast são é NW\n");
                insertInQuadTree(quadTree->nw, asteroid);
                break;
            case 1:
                printf("ast são é NE\n");  
                insertInQuadTree(quadTree->ne, asteroid);
                break;
            case 2:
                printf("ast são é SW\n");
                insertInQuadTree(quadTree->sw, asteroid);
                break;
            case 3:
                printf("ast são é SE\n");
                insertInQuadTree(quadTree->se, asteroid);
                break;
        }
    }




    /*
    printf("INSERT TREE CHAMADA\n");
    //checa se vai colocar na região do quadrado certo
    if(!contains(quadTree->boundary, asteroid->posX, asteroid->posY)){
        printf("o asteroid %d:%d não pertence a região {x=%d; y=%d w=%d h=%d}\n", asteroid->posX, asteroid->posY, quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w, quadTree->boundary.h);
        return;
    }
    /*
    if(quadTree->size < quadTree->capacity){
        quadTree->asteroid[quadTree->size++] = asteroid;
    }
    if(quadTree->asteroid == NULL){
        printf("ACHOU INSERT TREE asteroid %d:%d região {x=%d; y=%d w=%d h=%d} \n", asteroid->posX, asteroid->posY, quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w, quadTree->boundary.h);
        quadTree->asteroid = asteroid;
        //return;
    }
    /*
    if(quadTree->size == 0){
        printf("o no tinha nenhum asteroide alocado, aloquei o %d:%d região {x=%d; y=%d w=%d h=%d}\n", asteroid->posX, asteroid->posY, quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w, quadTree->boundary.h);
        quadTree->asteroid1 = asteroid;
        printf("quantidade de asteroides era :%d (da região{x=%d; y=%d w=%d h=%d})\n", quadTree->size, quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w, quadTree->boundary.h);
        quadTree->size++;
        printf("agora é: %d\n", quadTree->size);
    }else if(quadTree->size == 1){
        printf("o no tinha 1 asteroide alocado, aloquei o %d:%d região {x=%d; y=%d w=%d h=%d}\n", asteroid->posX, asteroid->posY, quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w, quadTree->boundary.h);
        quadTree->asteroid2 = asteroid;
        printf("quantidade de asteroides era :%d (da região{x=%d; y=%d w=%d h=%d})\n", quadTree->size, quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w, quadTree->boundary.h);
        quadTree->size++;
        printf("agora é: %d\n", quadTree->size);
    }
    
    else{
        printf("size é qualquer coisa diferente de 0 e 1\n");
        // subdividir
        if(!quadTree->divided){
        printf("quadtree precisou der dividida\n");
        printf("filhos {\n");      
        quadTree->nw = createTree(quadTree->boundary.x, quadTree->boundary.y, quadTree->boundary.w/2, quadTree->boundary.h/2);
        quadTree->ne = createTree(quadTree->boundary.x + quadTree->boundary.w/2, quadTree->boundary.y, quadTree->boundary.w/2, quadTree->boundary.h/2);
        quadTree->sw = createTree(quadTree->boundary.x , quadTree->boundary.y + quadTree->boundary.h/2, quadTree->boundary.w/2, quadTree->boundary.h/2);
        quadTree->se = createTree(quadTree->boundary.x + quadTree->boundary.w/2, quadTree->boundary.y + quadTree->boundary.h/2, quadTree->boundary.w/2, quadTree->boundary.h/2);

        quadTree->divided = 1;
        
        
        }
        printf("}fim filhos\n");      
        //insertInQuadTree(quadTree, asteroid);
        printf("INSERE NO LUGAR CERTO\n");   
        insertInQuadTree(quadTree->nw, asteroid);
        insertInQuadTree(quadTree->ne, asteroid);
        insertInQuadTree(quadTree->sw, asteroid);
        insertInQuadTree(quadTree->se, asteroid);

    }
    */
}
// pra inicialmente não haver colisões

void query(AsteroidList* asteroidList, QuadTree* quadTree, tCircle range){
    if(asteroidList == NULL) asteroidList = initList();

    if(!intersectsCircle(quadTree->boundary, range)){
        return;
    }
    if(quadTree->asteroid != NULL)
    if(containsPoint(range, quadTree->asteroid->posX, quadTree->asteroid->posY)) insertInList(asteroidList, quadTree->asteroid);
    //if(quadTree->asteroid2 != NULL)
    //if(containsPoint(range, quadTree->asteroid2->posX, quadTree->asteroid2->posY)) insertInList(asteroidList, quadTree->asteroid2);

    if(quadTree->type == 2){
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

void clearTree(QuadTree* quadTree){
    if(quadTree->type == 2){
        clearTree(quadTree->nw);
        clearTree(quadTree->ne);
        clearTree(quadTree->sw);
        clearTree(quadTree->se);
    }
    if(!(quadTree->nw == NULL)) free(quadTree->nw);
    if(!(quadTree->ne == NULL)) free(quadTree->ne);
    if(!(quadTree->sw == NULL)) free(quadTree->sw);
    if(!(quadTree->se == NULL)) free(quadTree->se);
    if(!(quadTree->asteroid == NULL)) free(quadTree->asteroid);
    //if(!(quadTree->asteroid2 == NULL)) free(quadTree->asteroid2);    



}





