#!/bin/bash
g++  -std=c++11 main.c -o main asteroid.c quadTree.c rectangle.c `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer
