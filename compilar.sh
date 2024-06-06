#!/bin/bash
cd build/
make clean; 
cmake -DCMAKE_BUILD_TYPE="Release" .. 
make -j4
cd ..

./build/ParchisGame
