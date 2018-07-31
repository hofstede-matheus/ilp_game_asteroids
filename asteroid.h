
#ifndef __ASTEROID_H__

#define __ASTEROID_H__ 1




typedef struct tAsteroid{ 
  int radius;
  // posição na tela
  int posX;
  int posY;
  // velocidade na tela
  int velX;
  int velY;
  /*
    0 = vermelho;
    1 = verde;
    2 = azul;
  */
  int color;
} Asteroid;
               
               
// ***********************************************
Asteroid* createAsteroid();
Asteroid* createAsteroidAtPosition(int x, int y, int r);
Asteroid* createAsteroidAtPosition(int x, int y, int r, int velX, int velY);
Asteroid* createProjectiel(int x, int y, int x2, int y2);
int sinal();

#endif //__ASTEROID_H__
    
