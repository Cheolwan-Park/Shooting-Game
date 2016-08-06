#!/bin/bash
./home/p552/Documents/shooting_game
cd ./obj/engine/
rm ./*.o
g++ -g -ggdb -W -Wall -O3 -c ./src/engine/*.cpp -std=c++11
