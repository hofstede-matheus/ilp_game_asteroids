
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
int sinal();

#endif //__ASTEROID_H__
    
