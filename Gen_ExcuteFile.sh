#!/bin/bash
rm ./test
g++ -W -Wall -g -ggdb  -O3 -o shooting ./shooting.cpp ./obj/engine/*.o ./obj/components/*.o -std=c++11 -lGL -lGLU -lglut -lfreeimage -lSDL -lSDL_mixer
