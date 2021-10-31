@echo off
g++ transform.cpp Content.cpp -o transform -std=c++11
transform 40 40 50 1 5
transform 80 80 50 2 10