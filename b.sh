# !/bin/bash
g++ main.cpp -o ./build/main `sdl2-config --cflags --libs`
./build/main
rm ./build/main
