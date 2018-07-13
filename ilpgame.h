/*
MIT License

Copyright (c) 2017 Rodrigo Rocha Gomes e Souza

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

----------------------------------

Biblioteca ILP Game, versão 1.0.1.

----------------------------------

A biblioteca ILP Game foi criada por Rodrigo Rocha Gomes e Souza, professor do
Departamento de Ciência da Computação da Universidade Federal da Bahia, em
julho de 2017, para apoiar a disciplina MATA37: Introdução à Lógica de
Programação (ILP).

Mais informações: https://rodrigorgs.github.io/ilpgame

----------------------------------


Para projetos com múltiplos arquivos de implementação (.cc, .cpp),
insira a linha

  #define ILPGAME_HEADER_ONLY

antes do #include "ilpgame.h" em todos os arquivos .cc/.cpp exceto um.

*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <cstdlib> // exit

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define DEFAULT_FPS (30)

using namespace std;

// https://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
// C++11
#define tostring(x) to_string(x)

////////////////////////////////////////////
// Funções definidas pelo usuário
////////////////////////////////////////////

void init();
void destroy();
void processEvent(SDL_Event event);
void update();
void draw();

#define changeScene(name) {\
  __destroy(); \
  changeFuncs(name ## _init, name ## _destroy, name ## _processEvent, name ## _update, name ## _draw); \
  __init(); \
}

////////////////////////////////////////////
// Cabeçalho
////////////////////////////////////////////

void initSDL_ttf();
void initSDL_image();
void initSDL_mixer();
void initSDL_base(int width, int height);
void initSDL(int width, int height);
void initSDL();
void cleanScreen(int r, int g, int b);
void cleanScreen();
void updateScreen();
void drawText(string text, TTF_Font *font, SDL_Color color, int x, int y);
void drawImage(SDL_Surface *surface, int x, int y);
void drawCenteredImage(SDL_Surface *surface, int x, int y);
void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b);
void limitFPS(int fps);
void disableFPSLimiting();
void endGameLoop();
void gameLoopIteration(void *arg);
void gameLoop();

bool isQuitEvent(SDL_Event event);
SDL_Surface *loadBMP(string filename);
SDL_Surface *loadImage(string filename);
TTF_Font *loadFont(string filename, int size);
Mix_Music *loadMusic(string filename);
Mix_Chunk *loadSound(string filename);
Mix_Music *loadMusic(string filename);
Mix_Chunk *loadSound(string filename);

void changeFuncs(void (*funcInit)(), void (*funcDestroy)(), void (*funcProcessEvent)(SDL_Event event), void (*funcUpdate)(), void (*funcDraw)());

////////////////////////////////////////////
// Variáveis globais
////////////////////////////////////////////

// Inspirado pela biblioteca EmbeddableWebServer.h
#ifndef ILPGAME_HEADER_ONLY

SDL_Window *window = NULL;
SDL_Surface *screen = NULL;
SDL_Renderer *renderer = NULL;

Uint32 lastTime = 0;
Uint32 minDeltaTime = 1000 / DEFAULT_FPS;
bool gameLoopQuit = false;

////////////////////////////////////////////
// Gerenciamento de cenas
////////////////////////////////////////////

void (*__init)() = init;
void (*__destroy)() = destroy;
void (*__processEvent)(SDL_Event event) = processEvent;
void (*__update)() = update;
void (*__draw)() = draw;

// void __init() {
//   if (sceneInit) {
//     sceneInit();
//   } else {
//     init();
//   }
// }
// void __destroy() {
//   if (sceneDestroy) {
//     sceneDestroy();
//   } else {
//     destroy();
//   }
// }
// void __processEvent(SDL_Event event) {
//   if (sceneProcessEvent) {
//     sceneProcessEvent(event);
//   } else {
//     processEvent(event);
//   }
// }
// void __update() {
//   if (sceneUpdate) {
//     sceneUpdate();
//   } else {
//     update();
//   }
// }
// void __draw() {
//   if (sceneDraw) {
//     sceneDraw();
//   } else {
//     draw();
//   }
// }

void changeFuncs(void (*funcInit)(), void (*funcDestroy)(), void (*funcProcessEvent)(SDL_Event event), void (*funcUpdate)(), void (*funcDraw)()) {
  __init = funcInit;
  __destroy = funcDestroy;
  __processEvent = funcProcessEvent;
  __update = funcUpdate;
  __draw = funcDraw;
}

void changeToDefaultScene() {
  __destroy();
  changeFuncs(init, destroy, processEvent, update, draw);
  __init();
}


////////////////////////////////////////////
// Inicializacao
////////////////////////////////////////////

void quit() {
  __destroy();

  if (TTF_WasInit()) {
    TTF_Quit();
  }
  while (Mix_Init(0)) {
    Mix_Quit();
  }
  Mix_CloseAudio();

  if (screen) {
    SDL_FreeSurface(screen);
    screen = NULL;
  }
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
  }
  if (window) {
    SDL_DestroyWindow(window);
    window = NULL;
  }

  SDL_Quit();
}

void initSDL_ttf() {
  if (TTF_Init() == -1) {
    cerr << "TTF_Init error: " << TTF_GetError() << endl;
    exit(1);
  }
}

void initSDL_image() {
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
    exit(1);
  }
}

void initSDL_mixer() {
  int flags = 0;
  int initted = Mix_Init(flags);
  if ((initted & flags) != flags) {
    cerr << "SDL mixer init error: " << Mix_GetError() << endl;
    exit(1);
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    cerr << "SDL init audio error: " << SDL_GetError() << endl;
    exit(1);
  }
}

void initSDL_base(int width, int height) {
  Uint32 flags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS;

  if (SDL_Init(flags) < 0) {
    cerr << "SDL init error: " << SDL_GetError() << endl;
    exit(1);
  }

  window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (!window) {
    cerr << "Error creating window: " << SDL_GetError() << endl;
    exit(1);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (!renderer) {
    cerr << "Error creating renderer: " << SDL_GetError() << endl;
    exit(1);
  }

  screen = SDL_GetWindowSurface(window);
}

void initSDL(int width, int height) {
  atexit(quit);
  initSDL_base(width, height);
  initSDL_image();
  initSDL_ttf();
  initSDL_mixer();
}

void initSDL() {
  initSDL(800, 600);
}


/////////////////////////////////////////
// Carga
/////////////////////////////////////////

SDL_Surface *loadBMP(string filename) {
  SDL_Surface *image = SDL_LoadBMP(filename.c_str());
  if (!image) {
    cerr << "Error loading image: %s" << SDL_GetError() << endl;
    exit(1);
  }
  return image;
}

// Adaptado de http://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index2.php
SDL_Surface *loadImage(string filename) {
  SDL_Surface* optimizedSurface = NULL;

  SDL_Surface* loadedSurface = IMG_Load(filename.c_str());
  if (!loadedSurface) {
    cerr << "Unable to load image " << filename << endl;
    cerr << "SDL_image Error: " << IMG_GetError() << endl;
    exit(1);
  }

  optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, 0);
  if (!optimizedSurface) {
    cerr << "Unable to optimize image " << filename << endl;
    cerr << "SDL Error: " << SDL_GetError() << endl;
    exit(1);
  }

  SDL_FreeSurface(loadedSurface);

  return optimizedSurface;
}

TTF_Font *loadFont(string filename, int size) {
  TTF_Font *font = TTF_OpenFont(filename.c_str(), size);
  if (font == NULL) {
    cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
    exit(1);
  }
  return font;
}

//////////////////////////////////////
// Desenho
//////////////////////////////////////

void cleanScreen(int r, int g, int b) {
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, r, g, b));
}

void cleanScreen() {
  cleanScreen(0, 0, 0);
}

void updateScreen() {
  SDL_UpdateWindowSurface(window);
}

void drawText(string text, TTF_Font *font, SDL_Color color, int x, int y) {
  SDL_Rect pos = {x, y, 0, 0};
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (!textSurface) {
    cerr << "Erro: drawText" << endl;
    exit(1);
  }
  SDL_BlitSurface(textSurface, NULL, screen, &pos);
  SDL_FreeSurface(textSurface);
}

void drawImage(SDL_Surface *surface, int x, int y) {
  if (surface) {
    SDL_Rect dest = {x, y, 0, 0};
    SDL_BlitSurface(surface, NULL, screen, &dest);
  } else {
    cerr << "Erro: drawImage com surface == NULL" << endl;
  }
}

void drawCenteredImage(SDL_Surface *surface, int x, int y) {
  drawImage(surface, x - surface->w / 2, y - surface->h / 2);
}

//////////////////////////////////////
// Desenho geométrico
//////////////////////////////////////

void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b) {
  SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

//////////////////////////////////////
// Audio
//////////////////////////////////////

#ifdef __EMSCRIPTEN__
// Disable music for now
Mix_Music *loadMusic(string filename) {
  return NULL;
}
Mix_Chunk *loadSound(string filename) {
  return NULL;
}
#define Mix_PlayChannel(a, b, c) cerr << "Mix_PlayChannel is disabled." << endl
#define Mix_PlayMusic(a, b) cerr << "Mix_PlayMusic is disabled." << endl
#define Mix_FreeChunk(a) cerr << "Mix_FreeChunk is disabled." << endl
#define Mix_FreeMusic(a) cerr << "Mix_FreeMusic is disabled." << endl
#else
Mix_Music *loadMusic(string filename) {
  Mix_Music *music = Mix_LoadMUS(filename.c_str());
  if (!music) {
    cerr << "Error loading " << filename << endl;
    exit(1);
  }
  return music;
}

Mix_Chunk *loadSound(string filename) {
  Mix_Chunk *chunk = Mix_LoadWAV(filename.c_str());
  if (!chunk) {
    cerr << "Error loading " << filename << endl;
    exit(1);
  }
  return chunk;
}
#endif


//////////////////////////////////////
// Frames per second (FPS)
//////////////////////////////////////

void limitFPS(int fps) {
  minDeltaTime = 1000 / fps;
}

void disableFPSLimiting() {
  minDeltaTime = 0;
}

//////////////////////////////////////
// Game loop
//////////////////////////////////////

bool isQuitEvent(SDL_Event event) {
#ifdef __EMSCRIPTEN__
  return false;
#else
  return event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE);
#endif
}

void endGameLoop() {
  gameLoopQuit = true;
}

void gameLoopIteration(void *arg) {
  SDL_Event event;

  if (minDeltaTime > 0) {
    lastTime = SDL_GetTicks();
  }

  while (SDL_PollEvent(&event) != 0 && !gameLoopQuit) {
    __processEvent(event);
  }

  if (!gameLoopQuit) {
    __update();
  }

  if (!gameLoopQuit) {
    SDL_RenderClear(renderer);
    cleanScreen();
    __draw();
    SDL_RenderPresent(renderer);
    updateScreen();
  }

  if (!gameLoopQuit && minDeltaTime > 0) {
    Uint32 deltaTime = SDL_GetTicks() - lastTime;
    if (deltaTime < minDeltaTime) {
      SDL_Delay(minDeltaTime - deltaTime);
    }
  }

#ifdef __EMSCRIPTEN__
  if (gameLoopQuit) {
    emscripten_cancel_main_loop();
  }
#endif
}

void gameLoop() {
  gameLoopQuit = false;

  __init();

#ifdef __EMSCRIPTEN__
  int simulate_infinite_loop = 1;
  emscripten_set_main_loop_arg(gameLoopIteration, NULL, -1, simulate_infinite_loop);
#else
  while (!gameLoopQuit) {
    gameLoopIteration(NULL);
  }
#endif

  // destroy() is called by quit(), which is called because of atexit()
}

#endif