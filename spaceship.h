//#include "ilpgame.h"
//#include "asteroidList.h"
//#include "quadTree.h"

#define TAM_CARRO 12

#define PI 3.14159265358979f

#define ACELERACAO 0.3f
#define FRENAGEM (ACELERACAO / 2)
#define DESACELERACAO (0.3 * ACELERACAO)
#define VELMAX 10.0f
#define VELANGULAR 0.1f


typedef struct {
  float x, y, x2, y2;
  float vel;
  float angle;
} Spaceship;


Spaceship* createSpaceship();
// void querySpaceshipCollision(AsteroidList** asteroidList, QuadTree* quadTree, int x, int y);
//void handleSpaceshipMoviment(const Uint8 *keyboard, Spaceship* spaceship);




