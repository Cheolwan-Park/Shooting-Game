#!/bin/bash
cd ./obj/components/
rm ./*.o
g++ -g -ggdb -W -Wall -O3 -c ./src/components/*.cpp -std=c++11
