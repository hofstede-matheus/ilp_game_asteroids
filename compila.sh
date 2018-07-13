#!/bin/bash
g++  -std=c++11 main.c -o main `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer
