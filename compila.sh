#!/bin/bash
g++ -g -std=c++11 main.c -o main asteroid.c quadTree.c rectangle.c asteroidList.c spaceship.c `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer
